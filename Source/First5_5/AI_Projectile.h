// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "AI_Projectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem; 
class AAICharacter;
class UNiagaraComponent;

UCLASS()
class FIRST5_5_API AAI_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAI_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDelayElapsed();

	FTimerHandle DelayTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float DelayDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerTag")
	FName PlayerTag = TEXT("PlayerDamage");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerTag")
	FName AITag = TEXT("RangedAI");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerTag")
	FName LandscapeTag = TEXT("Landscape");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerTag")
	bool BisHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* OnHitSound;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor> Explosion;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AAICharacter> AICharacterDontDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* EffectComp;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount;
};
