// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorAttributeComponent.h"
#include "NikaGameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "HealthPotion.h"

// Sets default values for this component's properties
UActorAttributeComponent::UActorAttributeComponent()
{
	HealthMax = 500.0f;
	Health = HealthMax;

	StaminaMax = 100.0f;
	Stamina = StaminaMax;

	PowerMax = 100;
	Power = PowerMax;
}

void UActorAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{

	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);

}

void UActorAttributeComponent::MulticastStaminaChanged_Implementation(AActor* InstigatorActor, float NewStamina, float Delta)
{

	OnStaminaChanged.Broadcast(InstigatorActor, this, NewStamina, Delta);

}

void UActorAttributeComponent::MulticastPowerChanged_Implementation(AActor* InstigatorActor, float NewPower, float Delta)
{

	OnPowerChanged.Broadcast(InstigatorActor, this, NewPower, Delta);

}

UActorAttributeComponent* UActorAttributeComponent::GetAttributes(AActor* FromActor)
{

	if (FromActor)
	{
		return FromActor->FindComponentByClass<UActorAttributeComponent>();
	}

	return nullptr;
}








bool UActorAttributeComponent::ApplyHealthChanged(AActor* InstigatorActor, float Delta)
{

	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);


	float ActualDelta = Health - OldHealth;
	//OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta);

	if (ActualDelta != 0)
	{
		MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
	}

	if (ActualDelta < 0 && Health == 0.0f)
	{

		ANikaGameModeBase* GM = GetWorld()->GetAuthGameMode<ANikaGameModeBase>();

		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}

	}


	return ActualDelta != 0;


}

bool UActorAttributeComponent::ApplyStamina(AActor* Instigator, float Delta)
{

	float OldStamina = Stamina;

	Stamina = FMath::Clamp(Stamina + Delta, 0.0f, StaminaMax);

	float ActualDelta = Stamina + OldStamina;

	if (ActualDelta != 0.0f)
	{
		MulticastStaminaChanged(Instigator, Stamina, ActualDelta);
	}
	return ActualDelta != 0;

}

bool UActorAttributeComponent::DepleteStamina(AActor* Instigator, float Delta)
{
	float OldStamina = Stamina;

	Stamina = FMath::Clamp(Stamina + Delta, 0.0f, StaminaMax);

	float ActualDelta = Stamina - OldStamina;

	if (ActualDelta != 0.0f)
	{
		MulticastStaminaChanged(Instigator, Stamina, ActualDelta);
	}
	return ActualDelta != 0;
}

bool UActorAttributeComponent::ApplyPower(AActor* Instigator, float Delta)
{

	float OldPower = Power;

	Power = FMath::Clamp(Power + Delta, 0.0f, PowerMax);

	float ActualDelta = Power + OldPower;

	if (ActualDelta != 0.0f)
	{
		MulticastPowerChanged(Instigator, Power, ActualDelta);
	}
	return ActualDelta != 0;

}

bool UActorAttributeComponent::DepletePower(AActor* Instigator, float Delta)
{
	float OldPower = Power;

	Power = FMath::Clamp(Power - Delta, 0.0f, PowerMax);

	float ActualDelta = Power - OldPower;

	if (ActualDelta != 0.0f)
	{
		MulticastPowerChanged(Instigator, Power, ActualDelta);
	}
	return ActualDelta != 0;
}

bool UActorAttributeComponent::IsAlive() const
{


	return Health > 0.0f;

}




bool UActorAttributeComponent::IsActorAlive(AActor* ActorStatus)
{

	UActorAttributeComponent* AttributeComp = GetAttributes(ActorStatus);

	if (AttributeComp)
	{
		
		return AttributeComp->IsAlive();
	}

	return false;
}

bool UActorAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

float UActorAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}



