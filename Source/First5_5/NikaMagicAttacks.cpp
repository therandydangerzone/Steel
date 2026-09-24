// Fill out your copyright notice in the Description page of Project Settings.


#include "NikaMagicAttacks.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"


UNikaMagicAttacks::UNikaMagicAttacks()
{

	AttackAnimDelay = 0.2f;
	HandSocketName = "Chest";
	SweepRadius = 64.0f;
	SweepDistanceFallback = 2500.0f;

}

void UNikaMagicAttacks::StartAction_Implementation(AActor* Instigator)
{

	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);

	if (Character)
	{

		/*
		FVector HandLocation = Character->GetMesh()->GetSocketLocation(HandSocketName);
		FVector TraceDirection = Character->GetControlRotation().Vector();
		const FVector TraceStart = Character->GetPawnViewLocation() + (TraceDirection + SweepRadius);
		const FVector TraceEnd = TraceStart + (TraceDirection * SweepDistanceFallback);
		FRotator ProjRotation = (TraceEnd - HandLocation).Rotation();
		Character->SetActorRotation(ProjRotation);
		*/
		UNiagaraComponent* NiagaraComp  = UNiagaraFunctionLibrary::SpawnSystemAttached(DashEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, FVector::ZeroVector, EAttachLocation::SnapToTarget, true,ENCPoolMethod::AutoRelease, true, true);

		Character->PlayAnimMontage(DashAnim);


		

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;

		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}

}

void UNikaMagicAttacks::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{

	if (ensureAlways(ProjectileClass))
	{

		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(SweepRadius);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FVector TraceDirection = InstigatorCharacter->GetControlRotation().Vector();

		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation() + (TraceDirection * SweepRadius);

		FVector TraceEnd = TraceStart + (TraceDirection * SweepDistanceFallback);
		

		FHitResult Hit;

		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel11, Shape, Params))
		{

			TraceEnd = Hit.ImpactPoint;

		}

		FRotator ProjRotation = (TraceEnd - HandLocation).Rotation();
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

	}
	StopAction(InstigatorCharacter);
}


