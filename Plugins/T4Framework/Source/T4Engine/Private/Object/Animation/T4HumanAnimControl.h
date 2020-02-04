// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Public/T4EngineUtility.h"
#include "T4BaseAnimControl.h"

/**
  *
 */
struct FT4IKFootInfo
{
	FT4IKFootInfo()
		: bEnableFootIK(true)
		, bInverseLeftFootOffset(false)
		, bInverseRightFootOffset(false)
		, CurrentCOMHeightOffset(0.0f)
	{
	}

	bool bEnableFootIK;

	bool bInverseLeftFootOffset;
	bool bInverseRightFootOffset;

	float CurrentCOMHeightOffset;
};

class FT4HumanAnimControl : public FT4BaseAnimControl
{
public:
	explicit FT4HumanAnimControl(AT4GameObject* InGameObject);
	virtual ~FT4HumanAnimControl();

public:
	// FT4BaseAnimControl
	void BeginPlay() override; // #18 : 모델 로딩이 완료된 시점에 1회 불림

	void SetAnimSetAsset(UT4AnimSetAsset* InAnimSetAsset) override; // #38
	void SetEnableFootIK(bool bInEnable) override { FootIKInfo.bEnableFootIK = bInEnable; }

	bool DoJump(const FVector& InVelocity) override; // #46
	bool DoRoll(const FVector& InVelocity) override; // #46
	bool DoTurn(const FRotator& InRotation) override; // #47
	bool DoVoid() override; // #76

	// #38
	bool IsStand() const { return CurrentVelocityNormal.IsNearlyZero(); }
	bool IsPrevStand() const { return PrevVelocityNormal.IsNearlyZero(); }
	bool IsMoving() const { return !CurrentVelocityNormal.IsNearlyZero(); }
	bool IsMoveStart() const { return IsPrevStand() && IsMoving(); } // #47
	bool IsMoveStop() const { return !IsPrevStand() && IsStand(); }

	const FName& GetDefaultUnarmedStanceStateName() const { return DefaultUnarmedStanceStateName; } // #48
	const FName& GetDefaultCombatStanceStateName() const { return DefaultCombatStanceStateName; } // #48
	const FName& GetDefaultRunningStateName() const { return DefaultRunningStateName; } // #48

	const FVector& GetJumpVelocity() const { return JumpVelocity; } // #47
	const FVector& GetRollVelocity() const { return RollVelocity; } // #47
	const FRotator& GetTurnGoalRotation() const { return TurnGoalRotation; } // #47

	const FVector& GetPrevVelocityNormal() const { return PrevVelocityNormal; }
	// ~#38

protected:
	void Reset() override; // #38
	void Advance(const FT4UpdateTime& InUpdateTime) override;

	void AutoRegisterAnimStates() override; // #47

	void NotifyPlayAnimation(const FT4AnimParameters& InAnimParameters) override; // #47

private:
	void AdvanceFootIK(const FT4UpdateTime& InUpdateTime);
	void ResetFootIK();

	bool CalaculateFootIKOffset(
		const FName& InSocketName, 
		float InAddTraceOffset,
		float& OutOffset,
		FVector* OutHitLocation = nullptr
	);

#if !UE_BUILD_SHIPPING
	void ApplyFootIKConsobleVar();
	void DebugDrawFootIKInfo(
		const FVector& InLeftFootHitLocation,
		const FVector& InRightFootHitLocation
	);
#endif

	void HandleOnAnimNotify(FName InNotifyName); // #38

protected:
	FName DefaultUnarmedStanceStateName; // #48
	FName DefaultCombatStanceStateName; // #48
	FName DefaultRunningStateName; // #48

	FT4IKFootInfo FootIKInfo;

	FVector CurrentVelocityNormal; // #38
	FVector PrevVelocityNormal; // #38

	// #46
	FVector JumpVelocity; 
	FVector RollVelocity;
	// ~#46
	FRotator TurnGoalRotation; // #47

	FT4HalfAngleInterpolator YawAngleLerp;
	FT4FloatInterpolator MoveSpeedLerp;
	FT4FloatInterpolator AimYawAngleLerp;
	FT4FloatInterpolator AimPitchAngleLerp;
};