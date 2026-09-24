// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include "MainCharacter.generated.h"



class UActorAttributeComponent;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class USunActions;
class USunActionComponent;
class UActorInteractionComponent;

UCLASS()
class FIRST5_5_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MYSQL")
	void ConnectToMySQL(FString Message);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UActorInteractionComponent* InteractionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Test;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Interact;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_LookStick;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_RockMagic;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Sprint;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Block;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Parry;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Dodge;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Dash;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Jump;


	UPROPERTY(EditDefaultsOnly, Category = "Input");
	TObjectPtr<UInputAction> Input_PrimaryAttackPower;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UActorAttributeComponent* AttributeComp;

	

	bool bHasPawnTarget;

	void Attack();

	void RockMagic();
	
	void PrimaryAttack();

	void PrimaryAttackTwo();

	void PrimaryAttackThree();

	void PrimaryAttackFour();

	void PrimaryAttackFive();

	void PrimaryAttackPower();

	void SprintStart();

	void SprintStop();

	void Block();

	void Dash();

	void Parry();

	void PrimaryInteractComp();

	void Dodge();

	void Move(const FInputActionInstance& Instance);
	
	void LookStick(const FInputActionValue& InputValue);
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	USunActions* Action;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	USunActionComponent* ActionComp;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool BisAttacking() const;

	UPROPERTY()
	bool isAttacking;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
