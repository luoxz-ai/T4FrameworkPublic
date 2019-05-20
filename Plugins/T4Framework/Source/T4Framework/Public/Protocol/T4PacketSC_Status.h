// Copyright 2019 Tech4 Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "T4PacketBase.h"
#include "T4PacketSC.h"
#include "T4PacketSC_Status.generated.h"

/**
  *
 */
 // #T4_ADD_PACKET_TAG

// ET4PacketStoC::Equip
// ET4PacketStoC::UnEquip
// ET4PacketStoC::Exchange

USTRUCT()
struct T4FRAMEWORK_API FT4PacketEquipSC : public FT4PacketStoC
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID ObjectID;

	UPROPERTY(VisibleAnywhere)
	FName ItemNameInTable;

public:
	FT4PacketEquipSC()
		: FT4PacketStoC(ET4PacketStoC::Equip)
		, ItemNameInTable(NAME_None)
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (!ObjectID.IsValid())
		{
			OutMsg = TEXT("Invalid ObjectID");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("SC_Packet:Equip"));
	}
};

USTRUCT()
struct T4FRAMEWORK_API FT4PacketUnEquipSC : public FT4PacketStoC
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID ObjectID;

	UPROPERTY(VisibleAnywhere)
	FName ItemNameInTable;

public:
	FT4PacketUnEquipSC()
		: FT4PacketStoC(ET4PacketStoC::UnEquip)
		, ItemNameInTable(NAME_None)
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (!ObjectID.IsValid())
		{
			OutMsg = TEXT("Invalid ObjectID");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("SC_Packet:UnEquip"));
	}
};

USTRUCT()
struct T4FRAMEWORK_API FT4PacketExchangeSC : public FT4PacketStoC
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FT4ObjectID ObjectID;

	UPROPERTY(VisibleAnywhere)
	FName ItemNameInTable;

public:
	FT4PacketExchangeSC()
		: FT4PacketStoC(ET4PacketStoC::Exchange)
		, ItemNameInTable(NAME_None)
	{
	}

	bool Validate(FString& OutMsg) override
	{
		if (!ObjectID.IsValid())
		{
			OutMsg = TEXT("Invalid ObjectID");
			return false;
		}
		return true;
	}

	FString ToString() const override
	{
		return FString(TEXT("SC_Packet:Exchange"));
	}
};