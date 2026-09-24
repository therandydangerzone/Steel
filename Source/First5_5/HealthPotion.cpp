// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include "ActorAttributeComponent.h"
#include "NikaPlayerState.h"


AHealthPotion::AHealthPotion()
{

	CreditCost;


}

void AHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{

		return;

	}

	UActorAttributeComponent* AttributeComp = UActorAttributeComponent::GetAttributes(InstigatorPawn);

	HideAndCooldownPowerup();


}

AHealthPotion* AHealthPotion::GetAttributes(AActor* FromActor)
{

	if (FromActor)
	{

		return Cast<AHealthPotion>(FromActor->GetComponentByClass(AHealthPotion::StaticClass()));

	}

	return nullptr;
}