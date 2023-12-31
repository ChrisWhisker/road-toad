// Copyright © Chris Worcester 2023 All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FroggerEditorTarget : TargetRules
{
	public FroggerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Frogger" } );
	}
}
