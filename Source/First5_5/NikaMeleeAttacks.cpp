// Fill out your copyright notice in the Description page of Project Settings.


#include "NikaMeleeAttacks.h"
#include "GameFramework/Character.h"
#include "SunProjectileActions.h"

UNikaMeleeAttacks::UNikaMeleeAttacks()
{

	AttackAnimDelay = 0.2f;
	HandSocketName;


}

void UNikaMeleeAttacks::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{

	StopAction(InstigatorCharacter);

}



void UNikaMeleeAttacks::StartAction_Implementation(AActor* Instigator)
{

	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);

	if (Character)
	{

		Character->PlayAnimMontage(AttackAnimation);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);


		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);

	}

}
