// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AInteractableObjects::AInteractableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopMesh"));
	TopMesh->SetupAttachment(BaseMesh);

	TreasureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreasureMesh"));
	TreasureMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110.0f;

}

void AInteractableObjects::Interact_Implementation(APawn* InstigatorPawn)
{

	//TopMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));

}

// Called when the game starts or when spawned
void AInteractableObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

