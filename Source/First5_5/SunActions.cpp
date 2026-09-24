// Fill out your copyright notice in the Description page of Project Settings.


#include "SunActions.h"
#include "SunActionComponent.h"

bool USunActions::BisRunning() const
{
	return isRunning;
}

bool USunActions::CanStart_Implementation(AActor* Instigator)
{

	if (BisRunning())
	{
		return false;
	}

	USunActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	
	return true;
}

void USunActions::StartAction_Implementation(AActor* Instigator)
{

	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));

	USunActionComponent* Comp = GetOwningComponent();

	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	isRunning = true;


}

void USunActions::StopAction_Implementation(AActor* Instigator)
{

	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));

	//ensureAlways(isRunning) was original line of code.

	(isRunning);

	USunActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	isRunning = false;

}

USunActionComponent* USunActions::GetOwningComponent() const
{
	return Cast<USunActionComponent>(GetOuter());
}


UWorld* USunActions::GetWorld() const
{

	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());

	if (Comp)
	{
		return Comp->GetWorld();
	}


	return nullptr;
}
