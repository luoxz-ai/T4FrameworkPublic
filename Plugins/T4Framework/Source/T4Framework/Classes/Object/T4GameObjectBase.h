// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Public/T4Framework.h" // #25, #42
#include "T4GameObjectBase.generated.h"

/**
  * #114 : BP 로 노출해서 게임 로직에서 사용한다.
 */
class UWorld;
class IT4Framework;
class IT4WorldActor;
class IT4WorldSystem;
UCLASS()
class T4FRAMEWORK_API UT4GameObjectBase : public UObject
{
	GENERATED_UCLASS_BODY()
		
	// Disable compiler-generated deprecation warnings by implementing our own destructor
	PRAGMA_DISABLE_DEPRECATION_WARNINGS
	virtual ~UT4GameObjectBase();
	PRAGMA_ENABLE_DEPRECATION_WARNINGS

public:
	void OnInitialize(ET4LayerType InLayerType, const FT4ObjectID& InObjectID);
	void OnFinalize();

	void OnProcess(float InDeltaTime);

	ET4LayerType GetLayerType() const { return LayerType; }
	const FT4ObjectID& GetObjectID() const { return ObjectID; } // #114

	virtual bool IsServerObject() const { return false; }
	virtual bool IsClientObject() const { return false; }

	virtual bool IsEntered() const { return false; } // #134

	virtual ET4ControllerType GetControllerType() const { return ET4ControllerType::Controller_Max; } // #114
	virtual IT4ObjectController* GetObjectController() const { return nullptr; } // #114 : Server All, Client Player Only

#if WITH_EDITOR
	virtual FString GetAIDebugString() const { return FString(); } // #114 : Only ServerObject
#endif

protected:
	virtual void Initialize() {}
	virtual void Finalize() {}

	virtual void Process(float InDeltaTime) {}

	UWorld* GetWorld() const;
	IT4Framework* GetFramework() const;
	IT4WorldSystem* GetWorldSystem() const;

	IT4WorldActor* FindWorldActor(const FT4ActorID& InActorID) const;

private:
	ET4LayerType LayerType;
	FT4ObjectID ObjectID;
};
