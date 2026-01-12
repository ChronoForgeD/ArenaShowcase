// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArenaShowcase : ModuleRules
{
	public ArenaShowcase(ReadOnlyTargetRules Target) : base(Target)
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

		PrivateDependencyModuleNames.AddRange(new string[] {"GameplayAbilities", "GameplayTags", "GameplayTasks" });

		PublicIncludePaths.AddRange(new string[] {
			"ArenaShowcase",
			"ArenaShowcase/Variant_Platforming",
			"ArenaShowcase/Variant_Platforming/Animation",
			"ArenaShowcase/Variant_Combat",
			"ArenaShowcase/Variant_Combat/AI",
			"ArenaShowcase/Variant_Combat/Animation",
			"ArenaShowcase/Variant_Combat/Gameplay",
			"ArenaShowcase/Variant_Combat/Interfaces",
			"ArenaShowcase/Variant_Combat/UI",
			"ArenaShowcase/Variant_SideScrolling",
			"ArenaShowcase/Variant_SideScrolling/AI",
			"ArenaShowcase/Variant_SideScrolling/Gameplay",
			"ArenaShowcase/Variant_SideScrolling/Interfaces",
			"ArenaShowcase/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
