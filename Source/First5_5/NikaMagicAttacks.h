// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SunActions.h"
#include "NikaMagicAttacks.generated.h"

class UAnimMontage;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class FIRST5_5_API UNikaMagicAttacks : public USunActions
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Effects")
	FName HandSocketName;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float AttibuteCost;

	UPROPERTY(EditAnywhere, Category = "Targeting")
	float SweepRadius;

	UPROPERTY(EditAnywhere, Category = "Targeting")
	float SweepDistanceFallback;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* DashAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

	UPROPERTY(EditAnywhere, Category = "Attack");
	UNiagaraSystem* DashEffect;

	virtual void StartAction_Implementation(AActor* Instigator) override;

	UNikaMagicAttacks();
	
};
