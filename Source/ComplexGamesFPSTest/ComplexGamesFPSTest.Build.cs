// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ComplexGamesFPSTest : ModuleRules
{
	public ComplexGamesFPSTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
