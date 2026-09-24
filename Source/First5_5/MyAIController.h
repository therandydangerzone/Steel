// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"


class UBehaviorTree;

/**
 * 
 */
UCLASS()
class FIRST5_5_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;

};
