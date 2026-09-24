// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "NikaGameModeBase.generated.h"


class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class ANikaPlayerState;

/**
 * 
 */
UCLASS()
class FIRST5_5_API ANikaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ANikaGameModeBase();

	virtual void StartPlay() override;

	FTimerHandle TimerHandle_SpawnBots;

	void SpawnBotTimerElapsed();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UEnvQuery> SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Kills")
	float AddKill;

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	UFUNCTION()
	void OnBotSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION(BlueprintCallable, Category = "Ben Gameplay")
	virtual void OnActorKilled(AActor* Killed, AActor* Shooter);

	UFUNCTION(BlueprintCallable, Category = "SQL Data")
	virtual void SQLKillCount(float KillTally);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	ANikaPlayerState* NPS;

};
