// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeEffects.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class FIRST5_5_API AHealthPotion : public AAttributeEffects
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "HealthPotion")
	int32 CreditCost;

public:

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static AHealthPotion* GetAttributes(AActor* FromActor);

	void Interact_Implementation(APawn* InstigatorPawn) override;

	AHealthPotion();
};
