// Copyright 2019 Tech4 Labs, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4EngineActionKey.h"
#include "T4EngineActionTypes.generated.h"

/**
  * http://api.unrealengine.com/KOR/Programming/UnrealArchitecture/Reference/Properties/
 */

// WARN : Action 추가 시는 아래 테그를 찾아 추가된 액션을 구현해주어야 함!!
// #T4_ADD_ACTION_TAG

UENUM()
enum class ET4ActionType : uint32
{
	Root, // #24

	// begin World

	ChangeWorld,

	ObjectEnter,
	ObjectLeave,

	// begin Object

	Possess,

	MoveAsyncTo, // #40
	MoveSyncTo, // #40
	JumpTo,
	RollTo, // #46
	TeleportTo,

	MoveStop, // #52
	MoveSpeedSync, // #52

	LockOn,

	EquipWeapon, // #22
	UnEquipWeapon, // #48
	ExchangeCostume, // #37

	Rotation,
	Animation,
	Particle,

	Conti, // #24

	Stop,

	// begin Editor
	EditorReload, // #37

	None,
};

// #24
UENUM()
enum class ET4LifecyclePolicy : uint8
{
	Duration,
	Looping,

	Default, // Default = Auto
};

UENUM()
enum class ET4MoveType : uint8
{
	Sync,
	Async,

	Current, // #52
	Count,
};

UENUM()
enum class ET4RotationType : uint8
{
	Current,

	TargetLocation,
	TargetDirection,
	TargetObject,

	TargetYawAngle, // #40, #44

	Default,
};

UENUM()
enum class ET4EditorReloadType : uint8
{
	All,
	Attribute,
	Data,

	None,
};