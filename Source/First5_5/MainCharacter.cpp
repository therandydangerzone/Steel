// Fill out your copyright notice in the Description page of Project Settings.




#include "MainCharacter.h"
#include "CoreMinimal.h"
#include "MYSQL.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SunActionComponent.h"
#include "Camera/CameraComponent.h"
#include "ActorInteractionComponent.h"
#include "ActorAttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "ThirdParty/MYSQLLibrary/Public/include/mysqlx/xdevapi.h"
#include <iostream>



// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Attribute Component
	AttributeComp = CreateDefaultSubobject<UActorAttributeComponent>("AttributeComp");

	//Interaction Component
	InteractionComp = CreateDefaultSubobject<UActorInteractionComponent>("InteractionComp");

	//Action Attack Component
	ActionComp = CreateDefaultSubobject<USunActionComponent>("ActionComp");


	//SpringArm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetUsingAbsoluteRotation(true);

	//CameraComp
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	//Movement 
	UCharacterMovementComponent* CharMoveComp = GetCharacterMovement();
	CharMoveComp->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	isAttacking = true;

	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::ConnectToMySQL(FString Message)
{




	try {


		std::string ConvertString = TCHAR_TO_UTF8(*Message);

		mysqlx::Session session("localhost", 33060, "rocks", "blackbeard");

		mysqlx::Schema db = session.getSchema("yes");

		mysqlx::Table table = db.getTable("test");

		table.insert("test").values(ConvertString).execute();

		UE_LOG(LogTemp, Warning, TEXT("it works"));

		session.close();
	}
	catch (const mysqlx::Error& err)
	{
		UE_LOG(LogTemp, Error, TEXT("MYSQL connection error: %s"), UTF8_TO_TCHAR(err.what()));
	}


}

void AMainCharacter::Attack() {

}
void AMainCharacter::RockMagic()
{

	ActionComp->StartActionByName(this, "RockMagic");

}
void AMainCharacter::PrimaryAttack()
{

	ActionComp->StartActionByName(this, "PrimaryAttack");

}
void AMainCharacter::PrimaryAttackTwo()
{

	ActionComp->StartActionByName(this, "PrimaryAttackTwo");

}
void AMainCharacter::PrimaryAttackThree()
{

	ActionComp->StartActionByName(this, "PrimaryAttackThree");

}
void AMainCharacter::PrimaryAttackFour()
{

	ActionComp->StartActionByName(this, "PrimaryAttackFour");

}
void AMainCharacter::PrimaryAttackFive()
{

	ActionComp->StartActionByName(this, "PrimaryAttackFive");

}
void AMainCharacter::PrimaryAttackPower()
{

	ActionComp->StartActionByName(this, "PrimaryAttackPower");

}
void AMainCharacter::SprintStart()
{

	ActionComp->StartActionByName(this, "Sprint");

}



void AMainCharacter::SprintStop()
{

	ActionComp->StopActionByName(this, "Sprint");

}

void AMainCharacter::Block()
{

	ActionComp->StartActionByName(this, "Block");

}

void AMainCharacter::Dash()
{

	ActionComp->StartActionByName(this, "Dash");

}

void AMainCharacter::Parry()
{

	ActionComp->StartActionByName(this, "Parry");

}

void AMainCharacter::PrimaryInteractComp()
{
	InteractionComp->PrimaryInteract();

}



void AMainCharacter::Dodge()
{

	ActionComp->StartActionByName(this, "Dodge");

}

void AMainCharacter::Move(const FInputActionInstance& Instance)
{

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// Get value from input (combined value from WASD keys or single Gamepad stick) and convert to Vector (x,y)
	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();

	// Move forward/back
	AddMovementInput(ControlRot.Vector(), AxisValue.Y);

	// Move Right/Left strafe
	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, AxisValue.X);

}
void AMainCharacter::LookStick(const FInputActionValue& InputValue)
{

	FVector2D Value = InputValue.Get<FVector2D>();

	// Track negative as we'll lose this during the conversion
	bool XNegative = Value.X < 0.f;
	bool YNegative = Value.Y < 0.f;

	// Can further modify with 'sensitivity' settings
	static const float LookYawRate = 100.0f;
	static const float LookPitchRate = 50.0f;

	// non-linear to make aiming a little easier
	Value = Value * Value;

	if (XNegative)
	{
		Value.X *= -1.f;
	}
	if (YNegative)
	{
		Value.Y *= -1.f;
	}

	// Aim assist
	 //todo: may need to ease this out and/or change strength based on distance to target
	float RateMultiplier = 1.0f;
	if (bHasPawnTarget)
	{
		RateMultiplier = 0.5f;
	}

	AddControllerYawInput(Value.X * (LookYawRate * RateMultiplier) * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput(Value.Y * (LookPitchRate * RateMultiplier) * GetWorld()->GetDeltaSeconds());

}
bool AMainCharacter::BisAttacking() const
{
	return isAttacking;
}
// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = GetController<APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	Subsystem->AddMappingContext(DefaultInputMapping, 0);

	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Test input
	InputComp->BindAction(Input_Test, ETriggerEvent::Triggered, this, &AMainCharacter :: Attack);

	//Attacks
	InputComp->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &AMainCharacter::PrimaryAttack);
	InputComp->BindAction(Input_PrimaryAttackPower, ETriggerEvent::Triggered, this, &AMainCharacter::PrimaryAttackPower);
	InputComp->BindAction(Input_RockMagic, ETriggerEvent::Triggered, this, &AMainCharacter::RockMagic);
	
	//Interact
	InputComp->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &AMainCharacter::PrimaryInteractComp);


	//Sprint
	
	InputComp->BindAction(Input_Sprint, ETriggerEvent::Started, this, &AMainCharacter::SprintStart);
	InputComp->BindAction(Input_Sprint, ETriggerEvent::Completed, this, &AMainCharacter::SprintStop);

	//
	InputComp->BindAction(Input_Parry, ETriggerEvent::Triggered, this, &AMainCharacter::Parry);

	//Block

	InputComp->BindAction(Input_Block, ETriggerEvent::Triggered, this, &AMainCharacter::Block);
	
	//Dash
	
	InputComp->BindAction(Input_Dash, ETriggerEvent::Triggered, this, &AMainCharacter::Dash);

	//Dodge

	InputComp->BindAction(Input_Dodge, ETriggerEvent::Triggered, this, &AMainCharacter::Dodge);

	//Jump
	
	InputComp->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);

	//Movement and line of sight

	InputComp->BindAction(Input_Move, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
	InputComp->BindAction(Input_LookStick, ETriggerEvent::Triggered, this, &AMainCharacter::LookStick);

}

