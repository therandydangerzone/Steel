// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SunActions.h"
#include "NikaMeleeAttacks.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class FIRST5_5_API UNikaMeleeAttacks : public USunActions
{
	GENERATED_BODY()

public:

	UNikaMeleeAttacks();

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> MeleeClass;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);


	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Targeting")
	float SweepRadius;

	UPROPERTY(EditAnywhere, Category = "Targeting")
	float SweepDistanceFallback;
	
	UPROPERTY(EditAnywhere, Category = "Melee Animation")
	UAnimMontage* AttackAnimation;

	UPROPERTY(EditAnywhere, Category = "Effects")
	FName HandSocketName;

	virtual void StartAction_Implementation(AActor* Instigator) override;
};
