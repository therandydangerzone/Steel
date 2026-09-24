// Fill out your copyright notice in the Description page of Project Settings.


#include "NikaGameModeBase.h"
#include "AICharacter.h"
#include "EngineUtils.h"
#include "MainCharacter.h"
#include "ActorAttributeComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/GameStateBase.h"
#include "NikaPlayerState.h"
#include "MYSQL.h"
#include "ThirdParty/MYSQLLibrary/Public/include/mysqlx/xdevapi.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);

ANikaGameModeBase::ANikaGameModeBase()
{

	AddKill = 0.0f;
	PlayerStateClass = ANikaPlayerState::StaticClass();
}

void ANikaGameModeBase::StartPlay()
{

	Super::StartPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ANikaGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);

}

void ANikaGameModeBase::SpawnBotTimerElapsed()
{


	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		return;
	}



	int32 NumOfAliveBots = 0;
	for (AAICharacter* Bot : TActorRange<AAICharacter>(GetWorld()))
	{


		UActorAttributeComponent* AttributeComp = UActorAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NumOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots."), NumOfAliveBots);

	float MaxBotCount = 10.0;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum Bot Capacity. No more spawning"));
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		//QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ADTwoGMBase::OnQueryCompleted);
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ANikaGameModeBase::OnBotSpawnQueryCompleted);
	}

}

void ANikaGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{

		Controller->UnPossess();
		RestartPlayer(Controller);

	}
}

void ANikaGameModeBase::OnBotSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{



	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

		//DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}

}

void ANikaGameModeBase::OnActorKilled(AActor* Killed, AActor* Shooter)
{
	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(Killed), *GetNameSafe(Shooter));

	/*
	AMainCharacter* Player = Cast<AMainCharacter>(Killed);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}
	*/
	
	APawn* KillerPawn = Cast<APawn>(Shooter);
	


	if (KillerPawn)
	{

		

			ANikaPlayerState* PS = KillerPawn->GetPlayerState<ANikaPlayerState>();
			if (PS)
			{
				PS->AddKills(AddKill);
				
			}



			/*
			try {


				mysqlx::Session session("localhost", 33060, "rocks", "blackbeard");

				mysqlx::Schema db = session.getSchema("yes");

				mysqlx::Table table = db.getTable("kc");

				//table.insert("KA").values(AddKill).execute();

				table.insert("KA").values(PS->KillCounter(AddKill)).execute();

				UE_LOG(LogTemp, Warning, TEXT("it works"));

				session.close();
			}
			catch (const mysqlx::Error& err)
			{
				UE_LOG(LogTemp, Error, TEXT("MYSQL connection error: %s"), UTF8_TO_TCHAR(err.what()));
			}
			*/


	}



}

void ANikaGameModeBase::SQLKillCount(float KillTally)
{
	

	try {


		mysqlx::Session session("localhost", 33060, "rocks", "blackbeard");

		//mysqlx::Session session("mysqlx://rocks:blackbeard@localhost:33060");

		mysqlx::Schema db = session.getSchema("yes");

		mysqlx::Table table = db.getTable("kc");

		table.insert("KA").values(KillTally).execute();

		UE_LOG(LogTemp, Warning, TEXT("it works"));

		session.close();

		
	}
	catch (const mysqlx::Error& err)
	{
		UE_LOG(LogTemp, Error, TEXT("MYSQL connection error: %s"), UTF8_TO_TCHAR(err.what()));
	}



}



