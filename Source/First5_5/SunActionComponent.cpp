// Fill out your copyright notice in the Description page of Project Settings.


#include "SunActionComponent.h"
#include "GameplayTagContainer.h"
#include "SunActions.h"

// Sets default values for this component's properties
USunActionComponent::USunActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USunActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<USunActions> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
	
}


// Called every frame
void USunActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + ":" + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);
}

USunActions* USunActionComponent::GetAction(TSubclassOf<USunActions> ActionClass) const
{

	for (USunActions* Action : Actions)
	{
		if (Action && Action->IsA(ActionClass))
		{
			return Action;
		}
	}

	return nullptr;
}

void USunActionComponent::AddAction(AActor* Instigator, TSubclassOf<USunActions> ActionClass)
{

	if (!(ActionClass))
	{
		return;
	}

	USunActions* NewAction = NewObject <USunActions>(this, ActionClass);
	if (ensure(NewAction))
	{

		Actions.Add(NewAction);

		if (NewAction->autoStart && ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}

	}

}

bool USunActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{

	for (USunActions* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{

			if (!Action->CanStart(Instigator))
			{
				continue;
			}

			Action->StartAction(Instigator);

			return true;
		}
	}

	return false;
}

bool USunActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{

	for (USunActions* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->BisRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}


	return false;
}

void USunActionComponent::RemoveAction(USunActions* ActionToRemove)
{
	if (ensure(ActionToRemove && !ActionToRemove->BisRunning()))
	{

		return;

	}

	Actions.Remove(ActionToRemove);

}

