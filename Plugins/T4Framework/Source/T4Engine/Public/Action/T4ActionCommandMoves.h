// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4ActionCommandBase.h"
#include "T4ActionCommandMoves.generated.h"

/**
  *
 */
 // #T4_ADD_ACTION_TAG_CMD

// ET4ActionCommandType::MoveAsync
// ET4ActionCommandType::MoveSync
// ET4ActionCommandType::Teleport
// ET4ActionCommandType::Jump
// ET4ActionCommandType::Roll
// ET4ActionCommandType::Rotation
// ET4ActionCommandType::Turn // #131

// ET4ActionCommandType::MoveStop // #52
// ET4ActionCommandType::MoveSpeedSync // #52

// ET4ActionCommandType::Launch // #63 : Only Projectile

// #40
USTRUCT()
struct T4ENGINE_API FT4MoveAsyncActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector MoveDirection;

	UPROPERTY(EditAnywhere)
	float HeadYawAngle; // #44 : degree, LockOn 일 경우 이동 방향과 달라진다.

public:
	FT4MoveAsyncActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, MoveDirection(FVector::ZeroVector)
		, HeadYawAngle(T4Const_EmptyYawAngle)
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::MoveAsync; }

	bool Validate(FString& OutMsg) override
	{
		if (MoveDirection.IsNearlyZero())
		{
			OutMsg = TEXT("Invalid MoveDirection");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("MoveAsyncToAction"));
	}
};

// #33, #40
USTRUCT()
struct T4ENGINE_API FT4MoveSyncActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector MoveVelocity; // #50

	UPROPERTY(EditAnywhere)
	float HeadYawAngle; // #40 : degree, LockOn 일 경우 이동 방향과 달라진다.

	UPROPERTY(EditAnywhere)
	bool bForceMaxSpeed; // #52 : MovementComponet::MaxSpeed 를 사용할지에 대한 Flag, 기본값이 false 로 Velocity 에서 Speed 를 얻는다. 동기화 이슈!!

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	FVector ServerNavPoint; // #52

	UPROPERTY(EditAnywhere)
	FVector ServerDirection; // #52
#endif

public:
	FT4MoveSyncActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, MoveVelocity(FVector::ZeroVector)
		, HeadYawAngle(T4Const_EmptyYawAngle)
		, bForceMaxSpeed(false) // #52
#if WITH_EDITORONLY_DATA
		, ServerNavPoint(FVector::ZeroVector) // #52
		, ServerDirection(FVector::ForwardVector) // #52
#endif
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::MoveSync; }

	bool Validate(FString& OutMsg) override
	{
		if (MoveVelocity.IsNearlyZero())
		{
			OutMsg = TEXT("Invalid MoveVelocity");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("MoveSyncToAction"));
	}
};

USTRUCT()
struct T4ENGINE_API FT4JumpActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector JumpVelocity;

public:
	FT4JumpActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, JumpVelocity(FVector::ZeroVector)
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::Jump; }

	bool Validate(FString& OutMsg) override
	{
		if (JumpVelocity.IsNearlyZero())
		{
			OutMsg = TEXT("Invalid JumpVelocity");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("JumpToAction"));
	}
};

// #46
USTRUCT()
struct T4ENGINE_API FT4RollActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector RollVelocity;

public:
	FT4RollActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, RollVelocity(FVector::ZeroVector)
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::Roll; }

	bool Validate(FString& OutMsg) override
	{
		if (RollVelocity.IsNearlyZero())
		{
			OutMsg = TEXT("Invalid RollVelocity");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("RollToAction"));
	}
};

// #34
USTRUCT()
struct T4ENGINE_API FT4TeleportActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector TargetLocation;

public:
	FT4TeleportActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, TargetLocation(FVector::ZeroVector)
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::Teleport; }

	bool Validate(FString& OutMsg) override
	{
		if (TargetLocation.IsNearlyZero())
		{
			OutMsg = TEXT("Invalid TargetLocation");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("TeleportToAction"));
	}
};

USTRUCT()
struct T4ENGINE_API FT4RotationActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	ET4TargetType TargetType;

	UPROPERTY(EditAnywhere)
	float RotationYawRate; // #44 : 초당 회전 단위, Yaw

	UPROPERTY(EditAnywhere)
	float TargetYawAngle; // #40 : LockOn 에서 방향을 맞출 경우 사용 (only ET4TargetType::TargetCustom)

public:
	FT4RotationActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, TargetType(ET4TargetType::Default)
		, RotationYawRate(0.0f)
		, TargetYawAngle(0.0f)
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::Rotation; }

	FString ToString() const override
	{
		return FString(TEXT("RotationAction"));
	}
};

// #131
USTRUCT()
struct T4ENGINE_API FT4TurnActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool bTurnRight;

	UPROPERTY(EditAnywhere)
	float TurnRate;

public:
	FT4TurnActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, bTurnRight(false)
		, TurnRate(500.0f)
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::Turn; }

	FString ToString() const override
	{
		return FString(TEXT("TurnAction"));
	}
};

// #52
USTRUCT()
struct T4ENGINE_API FT4MoveStopActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector StopLocation;

	UPROPERTY(EditAnywhere)
	float HeadYawAngle; // #40 : degree, LockOn 일 경우 이동 방향과 달라진다.

	UPROPERTY(EditAnywhere)
	bool bSyncLocation;

public:
	FT4MoveStopActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, StopLocation(FVector::ZeroVector)
		, HeadYawAngle(T4Const_EmptyYawAngle)
		, bSyncLocation(false)
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::MoveStop; }

	FString ToString() const override
	{
		return FString(TEXT("MoveStopAction"));
	}
};

// #52
USTRUCT()
struct T4ENGINE_API FT4MoveSpeedSyncActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	float MoveSpeed;

public:
	FT4MoveSpeedSyncActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, MoveSpeed(0.0f)
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::MoveSpeedSync; }

	FString ToString() const override
	{
		return FString(TEXT("MoveSpeedSyncAction"));
	}
};

// #63
USTRUCT()
struct T4ENGINE_API FT4LaunchActionCommand : public FT4ActionCommandBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FT4ActorID OwnerActorID; // #112

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<class UT4ActionSetAsset> HeadActionSetAsset;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UT4ActionSetAsset> EndActionSetAsset;

	UPROPERTY(EditAnywhere)
	ET4LoadingPolicy LoadingPolicy;

	UPROPERTY(EditAnywhere)
	float MaxPlayTimeSec; // #63 : Conti 의 MaxPlaytTimeSec 또는 서버에서 계산된 Hit 시간까지의 ProjectileDurationSec

	UPROPERTY(EditAnywhere)
	ET4ProjectileMotion ProjectileMotion; // #127

	UPROPERTY(EditAnywhere)
	ET4AcceleratedMotion AcceleratedMotion; // #127

	UPROPERTY(EditAnywhere)
	float InitialVerticalSpeed; // #127 : 곡사포(Parabola) 에서 사용될 초기 수직 속도

	UPROPERTY(EditAnywhere)
	bool bRandomRollAngle; // #127

	UPROPERTY(EditAnywhere)
	float InitialRollAngle; // #127

	UPROPERTY(EditAnywhere)
	bool bEnableHitAttached; // #112 : 충돌 지점에 잔상을 남길지 여부 (Arrow : true, Fireball : false)

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bEnableHitAttached"))
	float HitAttachedTimeSec; // #112 : 충돌 지점에 잔상 시간

	UPROPERTY(EditAnywhere)
	bool bEnableBounceOut; // #127 : 명확한 타겟없이 무한대로 발사될 경우 부딪히는 효과 처리 사용 여부

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bEnableBounceOut"))
	TSoftObjectPtr<UT4ActionSetAsset> BounceOutActionSetAsset;

	UPROPERTY(EditAnywhere)
	bool bUseOscillate; // #127 : 흔들림 여부

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bUseOscillate"))
	float OscillateRange; // #127 : 흔들림 크기

	UPROPERTY(EditAnywhere)
	float ProjectileLength; // #112 : Projectile 의 길이, 충돌 계산에서 Offset 으로 사용. (원점 에서의 길이)

	UPROPERTY(EditAnywhere)
	float ThrowOffsetTimeSec; // #63 : Projectile 로딩시간이 길어져 이미 발사 되었을 경우의 타이밍 맞추기
	
public:
	FT4LaunchActionCommand()
		: FT4ActionCommandBase(StaticActionType())
		, LoadingPolicy(ET4LoadingPolicy::Default)
		, MaxPlayTimeSec(0.0f)
		, ProjectileMotion(ET4ProjectileMotion::Straight) // #127
		, AcceleratedMotion(ET4AcceleratedMotion::Uniform) // #127
		, InitialVerticalSpeed(0.0f) // #127 : 곡사포(Parabola) 에서 사용될 초기 수직 속도
		, bRandomRollAngle(false) // #127
		, InitialRollAngle(0.0f) // #127
		, bEnableHitAttached(false)// #112
		, HitAttachedTimeSec(1.0f) // #112
		, bEnableBounceOut(false) // #127 : 명확한 타겟없이 무한대로 발사될 경우 부딪히는 효과 처리 사용 여부
		, bUseOscillate(false) // #127 : 흔들림 여부
		, OscillateRange(0.0f) // #127 : 흔들림 크기
		, ProjectileLength(80.0f) // #112
		, ThrowOffsetTimeSec(0.0f)
	{
	}

	static ET4ActionCommandType StaticActionType() { return ET4ActionCommandType::Launch; }

	FString ToString() const override
	{
		return FString(TEXT("LaunchAction"));
	}
};