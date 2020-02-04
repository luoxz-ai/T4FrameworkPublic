// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4ActionTypes.generated.h"

/**
  * http://api.unrealengine.com/KOR/Programming/UnrealArchitecture/Reference/Properties/
 */

static const float T4Const_ContiMaxPlayTimeSec = 10.0f; // #56
static const float T4Const_EmptyYawAngle = TNumericLimits<float>::Max(); // #113

// WARN : Action 추가 시는 아래 테그를 찾아 추가된 액션을 구현해주어야 함!!
// #T4_ADD_ACTION_TAG

UENUM()
enum class ET4ActionCommandType : uint32
{
	// #62
	Code,
	Conti,

	None,
};

UENUM()
enum class ET4ActionType : uint32
{
	// #62 : Begin Conti Format // #T4_ADD_ACTION_TAG_CONTI
	Branch, // #54

	SpecialMove, // #54

	Animation,
	
	Mesh, // #108
	Particle,
	Decal, // #54

	Projectile, // #63

	Reaction, // #76
	PlayTag, // #81

	TimeScale, // #102

	CameraWork, // #54
	CameraShake, // #101

	PostProcess, // #100
	Environment, // #99

	// #62 : End Conti Format

	// #62 : Start Code Format

	// begin World

	WorldTravel,

	SpawnObject,
	DespawnObject,

	// begin Object / #68 : #T4_ADD_ACTION_TAG_CODE

	MoveAsync, // #40
	MoveSync, // #40
	
	Jump,
	Roll, // #46
	Teleport,
	Turn,

	MoveStop, // #52
	MoveSpeedSync, // #52

	Launch, // #63 : Only Projectile

	Aim, // #113
	LockOn,

	Stance, // #73
	SubStance, // #106

	EquipWeapon, // #22
	UnequipWeapon, // #48
	Costume, // #37

	Hit, // #76

	Die, // #76
	Resurrect, // #76

	Conti, // #24

	Stop,
	
	Dummy, // #56 : Conti Editor 에서 Invisible or Isolate 로 출력을 제어할 때 더미용으로 사용 (delay, duration 동작 보장)

	// begin Editor
	Editor, // #37

	// #62 : End Code Format

	None,
};

// #24
UENUM()
enum class ET4LifecycleType : uint8
{
	Auto, // #56
	Duration,

	Looping		UMETA(DisplayName = "Looping (Warning #1)"), // #74

	Default, // Default = Auto
};

UENUM()
enum class ET4LoadingPolicy : uint8
{
	Async, // Default

	Sync, // #8, #56 : 사용 제한 필요!!! 만약을 대비해 준비는 해둔 것!

	Default UMETA(Hidden) // Default = Async
};

// #54
UENUM()
enum class ET4BranchCondition : uint8
{
	Always,
	
	CompareActiveName,

	Default, // Default = Auto
};

UENUM()
enum class ET4AttachParent : uint8 // #54
{
	Object, // Default
	World,

	Default,
};

UENUM()
enum class ET4PlayTarget : uint8 // #100
{
	Player, // Default
	All,

	Default,
};

// #102 : ref EMovieSceneBuiltInEasing
UENUM()
enum class ET4BuiltInEasing : uint8
{
	Linear UMETA(Grouping = Linear),

	// Sinusoidal easing
	SinIn UMETA(Grouping = Sinusoidal), SinOut UMETA(Grouping = Sinusoidal), SinInOut UMETA(Grouping = Sinusoidal),
	// Quadratic easing
	QuadIn UMETA(Grouping = Quadratic), QuadOut UMETA(Grouping = Quadratic), QuadInOut UMETA(Grouping = Quadratic),
	// Cubic easing
	CubicIn UMETA(Grouping = Cubic), CubicOut UMETA(Grouping = Cubic), CubicInOut UMETA(Grouping = Cubic),
	// Quartic easing
	QuartIn UMETA(Grouping = Quartic), QuartOut UMETA(Grouping = Quartic), QuartInOut UMETA(Grouping = Quartic),
	// Quintic easing
	QuintIn UMETA(Grouping = Quintic), QuintOut UMETA(Grouping = Quintic), QuintInOut UMETA(Grouping = Quintic),
	// Exponential easing
	ExpoIn UMETA(Grouping = Exponential), ExpoOut UMETA(Grouping = Exponential), ExpoInOut UMETA(Grouping = Exponential),
	// Circular easing
	CircIn UMETA(Grouping = Circular), CircOut UMETA(Grouping = Circular), CircInOut UMETA(Grouping = Circular),
};

UENUM()
enum class ET4PlayTagType : uint8 // #81
{
	Material, // #81
	Attachment, // #74
	Conti, // #74

	All, // #81
};