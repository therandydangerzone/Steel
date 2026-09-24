// Fill out your copyright notice in the Description page of Project Settings.


#include "SQLBPFunctionLib.h"
#include "ActorAttributeComponent.h"
#include "GameFramework/Actor.h"
#include "AI_Projectile.h"

bool USQLBPFunctionLib::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	

	UActorAttributeComponent* AttributeComp = UActorAttributeComponent::GetAttributes(TargetActor);
	if (AttributeComp)
	{
		return AttributeComp->ApplyHealthChanged(DamageCauser, -DamageAmount);
	}

	return false;
}

bool USQLBPFunctionLib::ApplyStamina(AActor* TargetActor, float StaminaAmount)
{
	UActorAttributeComponent* AttributeComp = UActorAttributeComponent::GetAttributes(TargetActor);

	if (AttributeComp->Stamina < 100.0f)
	{
		return AttributeComp->ApplyStamina(TargetActor, StaminaAmount);
	}

	return false;
}

bool USQLBPFunctionLib::DepleteStamina( AActor* TargetActor, float StaminaAmount)
{

	UActorAttributeComponent* AttributeComp = UActorAttributeComponent::GetAttributes(TargetActor);

	if (AttributeComp->Stamina <= 100.0f)
	{
		return AttributeComp->ApplyStamina(TargetActor, StaminaAmount);
	}

	return false;
}

bool USQLBPFunctionLib::PowerAdded(AActor* TargetActor, float PowerAmount)
{

	UActorAttributeComponent* AttributeComp = UActorAttributeComponent::GetAttributes(TargetActor);

	if (AttributeComp->Power < 100.0f)
	{
		return AttributeComp->ApplyPower(TargetActor, PowerAmount);
	}

	return false;
}

bool USQLBPFunctionLib::PowerTaken(AActor* TargetActor, float PowerAmount)
{

	UActorAttributeComponent* AttributeComp = UActorAttributeComponent::GetAttributes(TargetActor);

	if (AttributeComp->Power <= 100.0f)
	{
		return AttributeComp->DepletePower(TargetActor, PowerAmount);
	}

	return false;
}

bool USQLBPFunctionLib::ApplyHealthPotion(AActor* HealthAddedActor, AActor* InstigatorActor, float HealthAdded)
{

	UActorAttributeComponent* AttributeComp = UActorAttributeComponent::GetAttributes(InstigatorActor);
	if (AttributeComp)
	{
		return AttributeComp->ApplyHealthChanged(HealthAddedActor, HealthAdded);
	}

	return false;


}




