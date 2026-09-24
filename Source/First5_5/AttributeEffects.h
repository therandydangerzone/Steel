// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayInterface.h"
#include "GameFramework/Actor.h"
#include "AttributeEffects.generated.h"


class USphereComponent;
class UNiagaraSystem;
class UStaticMeshComponent;

UCLASS()
class FIRST5_5_API AAttributeEffects : public AActor, public IGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttributeEffects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AttributeEffect")
	float RespawnTime;

	UFUNCTION()
	void ShowAttributeEffect();

	void HideAndCooldownPowerup();

	void SetPowerupState(bool bNewIsActive);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UFUNCTION(BlueprintCallable)
	void Interact_Implementation(APawn* InstigatorPawn) override;

};
