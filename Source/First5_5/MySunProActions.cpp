// Fill out your copyright notice in the Description page of Project Settings.


#include "MySunProActions.h"
#include "GameFramework/Character.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


UMySunProActions::UMySunProActions()
{
	AttackAnimDelay = 0.2f;
	HandSocketName;
	AttributeCost;
	SweepRadius = 20.0f;
	SweepDistanceFallback = 5000.0f;

}

void UMySunProActions::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{

	if (ProjectileClass)
	{

		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FVector TraceDirection = InstigatorCharacter->GetControlRotation().Vector();
		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation() + (TraceDirection + SweepRadius);
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

void UMySunProActions::StartAction_Implementation(AActor* Instigator)
{

	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);

	if (Character)
	{

		//Character->PlayAnimMontage(AttackAnim);

		UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, FVector::ZeroVector, EAttachLocation::SnapToTarget, false, ENCPoolMethod::None, false, false);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);

	}



}


