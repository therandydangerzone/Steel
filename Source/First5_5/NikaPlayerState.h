// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NikaPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnKillCountChanged, ANikaPlayerState*, PlayerState, float, NewKillCount, float, Delta);

/**
 * 
 */
UCLASS()
class FIRST5_5_API ANikaPlayerState : public APlayerState
{
	GENERATED_BODY()

public: 

	ANikaPlayerState();

	UFUNCTION(BlueprintCallable, Category = "Kills")
	float GetKills() const;

	UFUNCTION(BlueprintCallable, Category = "Kills")
	void AddKills(float Delta);

	UFUNCTION(BlueprintCallable, Category = "Kills")
	float KillCounter(float Delta);

	UFUNCTION(BlueprintCallable, Category = "Kills")
	bool RemoveKills(float Delta);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnKillCountChanged OnKillsChanged;

	UPROPERTY(EditDefaultsOnly, Category = "Kills")
	float Kills;

	
};
