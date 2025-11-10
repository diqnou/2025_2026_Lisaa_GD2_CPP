// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lisaa : ModuleRules
{
	public Lisaa(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Lisaa",
			"Lisaa/Variant_Platforming",
			"Lisaa/Variant_Platforming/Animation",
			"Lisaa/Variant_Combat",
			"Lisaa/Variant_Combat/AI",
			"Lisaa/Variant_Combat/Animation",
			"Lisaa/Variant_Combat/Gameplay",
			"Lisaa/Variant_Combat/Interfaces",
			"Lisaa/Variant_Combat/UI",
			"Lisaa/Variant_SideScrolling",
			"Lisaa/Variant_SideScrolling/AI",
			"Lisaa/Variant_SideScrolling/Gameplay",
			"Lisaa/Variant_SideScrolling/Interfaces",
			"Lisaa/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
