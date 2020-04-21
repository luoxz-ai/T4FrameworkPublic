// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class T4FrameworkBuiltinTarget : TargetRules
{
    // http://api.unrealengine.com/KOR/Programming/UnrealBuildSystem/TargetFiles/

    public T4FrameworkBuiltinTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

        ExtraModuleNames.AddRange(
            new string[] {
				"T4FrameworkBuiltin"
			} 
        );
	}
}
