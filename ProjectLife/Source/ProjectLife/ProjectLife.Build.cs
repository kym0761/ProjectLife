// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectLife : ModuleRules
{
	public ProjectLife(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//기본으로 존재한 모듈
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});

		//추가된 모듈
		PublicDependencyModuleNames.AddRange(new string[] {"AIModule", "GameplayTasks", "UMG", "NavigationSystem", "Niagara" });

		//PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		PrivateIncludePaths.AddRange(new string[] { "ProjectLife" /*,"ProjectLife/Ability", "ProjectLife/Animal", "ProjectLife/Base", "ProjectLife/Building",
			"ProjectLife/Conversation", "ProjectLife/Craft", "ProjectLife/Equipment", "ProjectLife/Farming",
			"ProjectLife/GamePlay", "ProjectLife/Grid", "ProjectLife/Inventory", "ProjectLife/Item",
			"ProjectLife/Library", "ProjectLife/Puzzle", "ProjectLife/Quest","ProjectLife/Route",
			"ProjectLife/Shopping", "ProjectLife/Storage", "ProjectLife/UI"*/ });
	}
}
