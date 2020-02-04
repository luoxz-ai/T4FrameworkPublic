// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#include "T4StaticMeshEquipment.h"

#include "Object/Component/T4StaticMeshComponent.h"
#include "Object/T4GameObject.h"

#include "T4Asset/Classes/Entity/T4WeaponEntityAsset.h" // #41
#include "T4Asset/Public/Entity/T4Entity.h"

#include "T4EngineInternal.h"

/**
  * #68, #107
 */
FT4StaticMeshEquipment::FT4StaticMeshEquipment(
	AT4GameObject* InOwnerObject,
	const FT4ActionKey& InActionKey
)
	: FT4BaseEquipment(InOwnerObject, InActionKey)
	, LoadState(ET4EquipLoadState::ELS_Ready)
{
}

FT4StaticMeshEquipment::~FT4StaticMeshEquipment()
{
}

void FT4StaticMeshEquipment::AttackPrepare(
	const FT4EntityKey& InEntityKey,
	FName InOverrideEquipPoint
)
{
	if (bAttached)
	{
		return;
	}
	const UT4WeaponEntityAsset* WeaponEntityAsset = T4AssetEntityManagerGet()->GetWeaponEntity(
		InEntityKey
	);
	if (nullptr == WeaponEntityAsset)
	{
		T4_LOG(
			Error,
			TEXT("Weapon Entity '%s' not found"),
			*(InEntityKey.ToString())
		);
		return;
	}
	const FT4EntityItemWeaponMeshData& MeshData = WeaponEntityAsset->MeshData;
	check(ET4EntityMeshType::StaticMesh == MeshData.MeshType);
	EquipPoint = (InOverrideEquipPoint != NAME_None) ? InOverrideEquipPoint : MeshData.EquipPointName; // #106;
	RelativeRotation = MeshData.RelativeRotation; // #108
	RelativeScale = MeshData.RelativeScale; // #108
	StanceName = MeshData.StanceName; // #111
	bOverlapEvent = MeshData.bOverlapEvent; // #106
	EntityKey = InEntityKey;
	ObjectPath = MeshData.StaticMeshAsset.ToSoftObjectPath();
	OnStartLoading();
}

void FT4StaticMeshEquipment::DetachPrepare()
{
}

void FT4StaticMeshEquipment::Reset()
{
	if (!MeshLoader.CheckReset())
	{
		MeshLoader.Reset();
	}
	ComponentPtr.Reset();
}

void FT4StaticMeshEquipment::Advance(const FT4UpdateTime& InUpdateTime)
{
	if (!IsParentLoaded())
	{
		return;
	}
	switch (LoadState)
	{
		case ET4EquipLoadState::ELS_Loading:
			AdvanceLoading(InUpdateTime);
			break;
		
		case ET4EquipLoadState::ELS_Loaded:
			AdvanceLoadComplete(InUpdateTime);
			break;

		case ET4EquipLoadState::ELS_TryAttach:
			AdvanceTryAttach(InUpdateTime);
			break;
	};
}

void FT4StaticMeshEquipment::AdvanceLoading(const FT4UpdateTime& InUpdateTime)
{
	check(ET4EquipLoadState::ELS_Loading == LoadState);

	if (MeshLoader.IsLoadFailed()) // Failed 먼저 체크!!
	{
		LoadState = ET4EquipLoadState::ELS_Failed;
	}
	else if (MeshLoader.IsLoadCompleted())
	{
		LoadState = ET4EquipLoadState::ELS_Loaded;
	}
}

void FT4StaticMeshEquipment::AdvanceLoadComplete(const FT4UpdateTime& InUpdateTime)
{
	check(ET4EquipLoadState::ELS_Loaded == LoadState);

	if (!IsAttachable())
	{
		return; // #111 : Pending 상태면 Ttach 를 기다린다.
	}

	check(OwnerObjectPtr.IsValid());
	check(!ComponentPtr.IsValid());
	ComponentPtr = NewComponentTemplate<UT4StaticMeshComponent>(OwnerObjectPtr.Get(), true);
	ComponentPtr->SetRelativeRotation(RelativeRotation); // #108
	ComponentPtr->SetRelativeScale3D(FVector(RelativeScale)); // #108
	SePrimitiveComponent(Cast<UPrimitiveComponent>(ComponentPtr.Get()));
	SetOverrideMaterials(Cast<UMeshComponent>(ComponentPtr.Get())); // #80
	{
		MeshLoader.Process(ComponentPtr.Get());
		MeshLoader.SetBinded();
		MeshLoader.Reset();
	}
	AddDynamicMaterialInstances(ComponentPtr.Get()); // #108
	UpdateMaterialOpacityParameter(); // #108

	LoadState = ET4EquipLoadState::ELS_TryAttach;
}

void FT4StaticMeshEquipment::AdvanceTryAttach(const FT4UpdateTime& InUpdateTime)
{
	check(ET4EquipLoadState::ELS_TryAttach == LoadState);

	if (!IsAttachable())
	{
		return; // #111 : Pending 상태면 Ttach 를 기다린다.
	}

	// #108 : EquipPoint 를 찾을때까지 재귀 처리 (Bow => Arrow)
	if (!AttachToParent(FAttachmentTransformRules::KeepRelativeTransform))
	{
		T4_LOG(
			Verbose,
			TEXT("Try Attach Equipment Failed")
		);
		return;
	}
	ClearOverrideMaterialLoader();

	LoadState = ET4EquipLoadState::ELS_Completed;
}

void FT4StaticMeshEquipment::StartLoading()
{
	LoadState = ET4EquipLoadState::ELS_Ready;
	if (ObjectPath.IsNull())
	{
		LoadState = ET4EquipLoadState::ELS_NotSet;
		return;
	}
	MeshLoader.Load(ObjectPath, false, TEXT("Equipment_StaticMesh"));
	LoadState = ET4EquipLoadState::ELS_Loading;
}