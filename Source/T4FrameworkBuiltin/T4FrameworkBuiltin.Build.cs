// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

using UnrealBuildTool;

public class T4FrameworkBuiltin : ModuleRules
{
	public T4FrameworkBuiltin(ReadOnlyTargetRules Target) : base(Target)
	{
        // http://api.unrealengine.com/KOR/Programming/UnrealBuildSystem/IWYUReferenceGuide/
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
            new string[] 
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "T4Asset",
                "T4Engine",
                "T4Framework"
            }
        );

        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.Add("UnrealEd");
        }

        PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
