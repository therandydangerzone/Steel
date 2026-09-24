// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree, TEXT("Behavior tree is null please assign a tree."))
	{
		RunBehaviorTree(BehaviorTree);
	}

}
