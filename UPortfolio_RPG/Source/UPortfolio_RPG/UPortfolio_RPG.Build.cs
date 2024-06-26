// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UPortfolio_RPG : ModuleRules
{
	public UPortfolio_RPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
            ,"AIModule" , "Niagara","NavigationSystem", "GameplayTasks",
            "SlateCore", "Json",             
            "JsonUtilities",
            "ApplicationCore"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
        PublicIncludePaths.Add("UPortfolio_RPG");
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
