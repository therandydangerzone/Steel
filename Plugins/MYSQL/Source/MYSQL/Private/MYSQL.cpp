// Copyright Epic Games, Inc. All Rights Reserved.

#include "MYSQL.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"



#define LOCTEXT_NAMESPACE "FMYSQLModule"

void FMYSQLModule::StartupModule()
{

	FString BaseDir = IPluginManager::Get().FindPlugin("MYSQL")->GetBaseDir();

	
}

void FMYSQLModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMYSQLModule, MYSQL)
