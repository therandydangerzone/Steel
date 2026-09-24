// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeEffects.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAttributeEffects::AAttributeEffects()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	RespawnTime = 120.0f;
}

// Called when the game starts or when spawned
void AAttributeEffects::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAttributeEffects::ShowAttributeEffect()
{
	SetPowerupState(true);

}

void AAttributeEffects::HideAndCooldownPowerup()
{

	SetPowerupState(false);

	FTimerHandle TimerHandle_RespawnTimer;
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &AAttributeEffects::ShowAttributeEffect, RespawnTime);

	Destroy();

}

void AAttributeEffects::SetPowerupState(bool bNewIsActive)
{

	SetActorEnableCollision(bNewIsActive);
	RootComponent->SetVisibility(bNewIsActive, true);


}

// Called every frame
void AAttributeEffects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttributeEffects::Interact_Implementation(APawn* InstigatorPawn)
{
}

