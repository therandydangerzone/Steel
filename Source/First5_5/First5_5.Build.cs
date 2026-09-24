// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class First5_5 : ModuleRules
{
	public First5_5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayTags" ,"EnhancedInput", "Niagara" ,"MYSQL", "MYSQLLibrary" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });


		bEnableExceptions = true;

   
        //imported dlls.2
        DirectoryInfo DI2 = new DirectoryInfo(@"C:\MySQLMisc\mysql-connector-c++-9.3.0-winx64\lib64");
        FileInfo[] Files2 = DI2.GetFiles("*.dll");
        foreach (FileInfo file in Files2)
        {
            string FileName = Path.GetFileName(file.FullName);
            RuntimeDependencies.Add("$(BinaryOutputDir)/" + FileName, file.FullName);

        }
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
