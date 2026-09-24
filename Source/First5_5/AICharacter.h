// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "AICharacter.generated.h"

class UAnimMontage;
class UActorAttributeComponent;
class USunActionComponent;
class UUserWidget;
class GameplayTagContainer;
class USunUserWidget;

UCLASS()
class FIRST5_5_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(EditAnywhere, Category = "UI")
	USunUserWidget* ActiveHealthBar;

	UPROPERTY(EditAnywhere, Category = "UI")
	FName HealthSocketName;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void OnHealthChanged(AActor* InstigatorActor, UActorAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	//UFUNCTION(BluePrintCallable, Category = "AI")
	//void SetTargetActor(AActor* NewTarget);

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* DeathAnimation;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	

	UFUNCTION(Blueprintcallable, Category ="AI")
	AActor* GetTargetActor() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UActorAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	FName TargetActorKey;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USunActionComponent> ActionComp;

	virtual void InitializeComponent();

	virtual void PostInitializeComponents() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
