// Fill out your copyright notice in the Description page of Project Settings.


#include "DashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"


ADashProjectile::ADashProjectile()
{

	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComp->InitialSpeed = 8000.0f;


}
void ADashProjectile::BeginPlay()
{

	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ADashProjectile::Explode_Implementation, DetonateDelay);


}
void ADashProjectile::Explode_Implementation()
{

	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	
	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ProjectileVFX, GetActorLocation(), FRotator::ZeroRotator);

	

	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ADashProjectile::TeleportInstigator, TeleportDelay);
}

void ADashProjectile::TeleportInstigator()
{

	AActor* ActorToTeleport = GetInstigator();

	if (ActorToTeleport)
	{
		ActorToTeleport->GetActorLocation();

		

		FVector CurrentLocation = ActorToTeleport->GetActorLocation();
		
		float newXAxis = 500.0f;

		//FVector NewLocation = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, CurrentLocation.Z);

		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);

	}

}




