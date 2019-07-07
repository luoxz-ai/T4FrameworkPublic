// Copyright 2019 Tech4 Labs, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Public/T4FrameworkNet.h" // #25, #42
#include "Public/T4FrameworkAssetLoader.h" // #42
#include "Public/T4FrameworkController.h"

#include "T4Engine/Public/T4Engine.h"

#include "AIController.h"
#include "T4NPCAIController.generated.h"

/**
  * http://api.unrealengine.com/KOR/Gameplay/Framework/Controller/AIController/
 */

enum ET4AIDataLoadState // #50
{
	AIDataLoad_Ready,
	AIDataLoad_Loading,
	AIDataLoad_Loaded,
	AIDataLoad_NoData,
};

class UT4PathFollowingComponent;

UCLASS()
class T4FRAMEWORK_API AT4NPCAIController : public AAIController, public IT4NPCAIController
{
	GENERATED_UCLASS_BODY()

public:
	void PostInitializeComponents();

	virtual void TickActor(
		float InDeltaTime,
		enum ELevelTick InTickType,
		FActorTickFunction& InThisTickFunction
	) override;

	/** If true, actor is ticked even if TickType==LEVELTICK_ViewportsOnly	 */
	bool ShouldTickIfViewportsOnly() const override; // #17

	void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;

	void HandleOnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result); // #34

protected:
	void BeginPlay() override;

	// Begin AController interface
	void GameHasEnded(class AActor* EndGameFocus = NULL, bool bIsWinner = false) override;
	void OnPossess(class APawn* InPawn) override;
	void OnUnPossess() override;
	void BeginInactiveState() override;
	// End AController interface

public:
	// IT4GameController
	ET4LayerType GetLayerType() const override { return LayerType; }
	ET4GameControllerType GetGameControllerType() const override { return ET4GameControllerType::GameController_NPC; }

	bool SetGameObject(const FT4ObjectID& InNewTargetID) override;
	void ClearGameObject(bool bInSetDefaultPawn) override;

	bool HasGameObject() const override  { return GameObjectID.IsValid(); }
	const FT4ObjectID& GetGameObjectID() const override { return GameObjectID; }
	IT4GameObject* GetGameObject() const override;
	IT4ActionControl* GetGameObjectActionControl() const override;

	IT4GameWorld* GetGameWorld() const override; // #52

	bool HasPlayingAction(const FT4ActionKey& InActionKey) const override; // #20

	AController* GetAController() override;

public:
	void SetNetID(const FT4NetID& InNetID) { NetID = InNetID;}
	const FT4NetID& GetNetID() const { return NetID; }

protected:
	virtual void NotifyAIReady() {} // #50
	virtual void NotifyAIStart() {} // #50
	virtual void NotifyAIEnd() {} // #50

	IT4GameObject* FindGameObjectForServer(const FT4ObjectID& InObjectID) const; // #49

protected:
	ET4LayerType LayerType;

	FT4NetID NetID; // #15
	FT4ObjectID GameObjectID;

	UPROPERTY(transient)
	UT4PathFollowingComponent* OverridePathFollowingComponent; // #34
};
