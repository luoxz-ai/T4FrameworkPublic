// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "T4RehearsalEditor/Private/AssetTypeActions/AssetTypeActions_T4ContiAsset.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAssetTypeActions_T4ContiAsset() {}
// Cross Module References
	T4REHEARSALEDITOR_API UClass* Z_Construct_UClass_UT4ContiAsset_Factory_NoRegister();
	T4REHEARSALEDITOR_API UClass* Z_Construct_UClass_UT4ContiAsset_Factory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	UPackage* Z_Construct_UPackage__Script_T4RehearsalEditor();
// End Cross Module References
	void UT4ContiAsset_Factory::StaticRegisterNativesUT4ContiAsset_Factory()
	{
	}
	UClass* Z_Construct_UClass_UT4ContiAsset_Factory_NoRegister()
	{
		return UT4ContiAsset_Factory::StaticClass();
	}
	struct Z_Construct_UClass_UT4ContiAsset_Factory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UT4ContiAsset_Factory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_T4RehearsalEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UT4ContiAsset_Factory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "AssetTypeActions/AssetTypeActions_T4ContiAsset.h" },
		{ "ModuleRelativePath", "Private/AssetTypeActions/AssetTypeActions_T4ContiAsset.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UT4ContiAsset_Factory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UT4ContiAsset_Factory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UT4ContiAsset_Factory_Statics::ClassParams = {
		&UT4ContiAsset_Factory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UT4ContiAsset_Factory_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UT4ContiAsset_Factory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UT4ContiAsset_Factory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UT4ContiAsset_Factory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UT4ContiAsset_Factory, 3574484132);
	template<> T4REHEARSALEDITOR_API UClass* StaticClass<UT4ContiAsset_Factory>()
	{
		return UT4ContiAsset_Factory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UT4ContiAsset_Factory(Z_Construct_UClass_UT4ContiAsset_Factory, &UT4ContiAsset_Factory::StaticClass, TEXT("/Script/T4RehearsalEditor"), TEXT("UT4ContiAsset_Factory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UT4ContiAsset_Factory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
