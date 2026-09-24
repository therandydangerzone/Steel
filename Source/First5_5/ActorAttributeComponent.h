// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, UActorAttributeComponent*, OwningComp, float, NewAttribute, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRST5_5_API UActorAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorAttributeComponent();

protected:
	

public:	
	

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastStaminaChanged(AActor* InstigatorActor, float NewStamina, float Delta);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPowerChanged(AActor* InstigatorActor, float NewPower, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attibutes")
	static UActorAttributeComponent* GetAttributes(AActor* FromActor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = "Attributes")
	float Health;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float HealthMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float StaminaMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float Power;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
	float PowerMax;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static bool IsActorAlive(AActor* ActorStatus);

	UFUNCTION(BlueprintCallable)
	bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetHealthMax() const;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnPowerChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChanged(AActor* InstigatorActor ,float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyStamina(AActor* Instigator, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool DepleteStamina(AActor* Instigator, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyPower(AActor* Instigator, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool DepletePower(AActor* Instigator, float Delta);


	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const;

};
