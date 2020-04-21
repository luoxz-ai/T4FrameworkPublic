// Copyright 2019-2020 SoonBo Noh. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class T4FrameworkBuiltinEditorTarget : TargetRules
{
    // http://api.unrealengine.com/KOR/Programming/UnrealBuildSystem/TargetFiles/

    public T4FrameworkBuiltinEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

        ExtraModuleNames.AddRange(
            new string[] {
				"T4FrameworkBuiltin"
			}
        );
    }
}
