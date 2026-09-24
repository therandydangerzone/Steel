// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SQLBPFunctionLib.generated.h"

class AHealthPotion;
class AActor;
 
/**
 * 
 */
UCLASS()
class FIRST5_5_API USQLBPFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyStamina( AActor* TargetActor, float StaminaAmount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool DepleteStamina( AActor* TargetActor, float StaminaAmount);
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool PowerAdded(AActor* TargetActor, float PowerAmount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool PowerTaken(AActor* TargetActor, float PowerAmount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyHealthPotion(AActor* HealthAddedActor,AActor* InstigatorActor, float HealthAdded);

};
