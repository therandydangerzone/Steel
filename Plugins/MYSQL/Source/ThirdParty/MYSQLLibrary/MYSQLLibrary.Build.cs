// Fill out your copyright notice in the Description page of Project Settings.

using System.Diagnostics;
using System.IO;
using UnrealBuildTool;

public class MYSQLLibrary : ModuleRules
{
	public MYSQLLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

        /*
         // Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "ExampleLibrary.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("ExampleLibrary.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/MYSQLLibrary/Win64/ExampleLibrary.dll");

		PublicSystemIncludePaths.Add("$(ModuleDir)/Public/include/jdbc");
        PublicSystemIncludePaths.Add("$(ModuleDir)/Public/include/jdbc/cppconn");
        PublicSystemIncludePaths.Add("$(ModuleDir)/Public/include/mysql");
        PublicSystemIncludePaths.Add("$(ModuleDir)/Public/include/mysqlx");
        PublicSystemIncludePaths.Add("$(ModuleDir)/Public/include/mysqlx/common");
        PublicSystemIncludePaths.Add("$(ModuleDir)/Public/include/mysqlx/devapi");
        PublicSystemIncludePaths.Add("$(ModuleDir)/Public/include/mysqlx/devapi/detail");
        */

     


        if (Target.Platform == UnrealTargetPlatform.Win64)
		{

            string IncPath = Path.Combine(ModuleDirectory, "Public", "include", "mysql");
            PublicSystemIncludePaths.Add(IncPath);

            string IncPath2 = Path.Combine(ModuleDirectory, "Public", "include", "jdbc");
            PublicSystemIncludePaths.Add(IncPath2);

            string IncPath3 = Path.Combine(ModuleDirectory, "Public", "include", "jdbc", "cppconn");
            PublicSystemIncludePaths.Add(IncPath3);

            string IncPath4 = Path.Combine(ModuleDirectory, "Public", "include", "mysqlx");
            PublicSystemIncludePaths.Add(IncPath4);

            string IncPath5 = Path.Combine(ModuleDirectory, "Public", "include", "mysqlx", "common");
            PublicSystemIncludePaths.Add(IncPath5);

            string IncPath6 = Path.Combine(ModuleDirectory, "Public", "include", "mysqlx", "devapi");
            PublicSystemIncludePaths.Add(IncPath6);

            string IncPath7 = Path.Combine(ModuleDirectory, "Public", "include", "mysqlx", "devapi", "detail");
            PublicSystemIncludePaths.Add(IncPath7);

            //imports dlls.1
            DirectoryInfo DI = new DirectoryInfo(@"C:\MySQLMisc\mysql-connector-c++-9.3.0-winx64\bin");
            FileInfo[] Files = DI.GetFiles("*.dll");
            foreach (FileInfo file in Files)
            {
                string FileName = Path.GetFileName(file.FullName);
                RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/" + FileName, file.FullName);
                
            }


            //imported dlls.2
            DirectoryInfo DI2 = new DirectoryInfo(@"C:\MySQLMisc\mysql-connector-c++-9.3.0-winx64\lib64");
            FileInfo[] Files2 = DI2.GetFiles("*.dll");
            foreach (FileInfo file in Files2)
            {
                string FileName = Path.GetFileName(file.FullName);
                RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/" + FileName, file.FullName);
                
            }


            //imported dlls.3
            DirectoryInfo DI3 = new DirectoryInfo(@"C:\MySQLMisc\mysql-connector-c++-9.3.0-winx64\lib64\plugin");
            FileInfo[] Files3 = DI3.GetFiles("*.dll");
            foreach (FileInfo file in Files3)
            {
                string FileName = Path.GetFileName(file.FullName);
                RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/" + FileName, file.FullName);
                
            }


            



            //imported libaries

            
            DirectoryInfo DI4 = new DirectoryInfo(@"C:\MySQLMisc\mysql-connector-c++-9.3.0-winx64\lib64\vs14\");

            FileInfo[] Libs = DI4.GetFiles("*.lib");
            foreach (FileInfo file in Libs)
            {
                string FileName = Path.GetFileName(file.FullName);

                PublicAdditionalLibraries.Add(file.FullName);
                RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/" + FileName, file.FullName);

            }
            
            //imported debug

            DirectoryInfo DI5 = new DirectoryInfo(@"C:\MySQLMisc\mysql-connector-c++-9.3.0-winx64\lib64");
            FileInfo[] DB = DI5.GetFiles("*.pdb");

            foreach(FileInfo file in DB)
            {

                
                string FileName = Path.GetFileName(file.FullName);
                RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/" + FileName, file.FullName);
            }


        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/MYSQLLibrary/Mac/Release/libExampleLibrary.dylib");
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string ExampleSoPath = Path.Combine("$(PluginDir)", "Binaries", "ThirdParty", "MYSQLLibrary", "Linux", "x86_64-unknown-linux-gnu", "libExampleLibrary.so");
			PublicAdditionalLibraries.Add(ExampleSoPath);
			PublicDelayLoadDLLs.Add(ExampleSoPath);
			RuntimeDependencies.Add(ExampleSoPath);
		}
	}
}
