// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Camera/CameraComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"
#include "BrainComponent.h"
#include "ActorAttributeComponent.h"
#include "MYSQL.h"
#include "SunActionComponent.h"
#include "ThirdParty/MYSQLLibrary/Public/include/mysqlx/xdevapi.h"
#include "ActorAttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "SunUserWidget.h"



// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeComp = CreateDefaultSubobject<UActorAttributeComponent>("AttributeComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	ActionComp = CreateDefaultSubobject<USunActionComponent>("ActionComp");

	//GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetGenerateOverlapEvents(true);

	

	HealthSocketName;

	TargetActorKey = "TargetActor";
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAICharacter::PostInitializeComponents()
{

	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AAICharacter::OnHealthChanged);

}

void AAICharacter::InitializeComponent()
{

	ActionComp->Activate(true);

}

void AAICharacter::OnHealthChanged(AActor* InstigatorActor, UActorAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f) 
	{
		
		
		AAIController* AIC = Cast<AAIController>(GetController());

		if (NewHealth <= 0.0f)
		{

		if (AIC)
		{
			AIC->GetBrainComponent()->StopLogic("Killed");
		}

		//GetMesh()->SetAllBodiesSimulatePhysics(true);
		//GetMesh()->SetCollisionProfileName("Ragdoll");
		GetCharacterMovement()->DisableMovement();
		}
	
		
		/*
		if (ActiveHealthBar == nullptr)
		{
		ActiveHealthBar = CreateWidget<USunUserWidget>(GetWorld(), HealthBarWidgetClass);
		if (ActiveHealthBar)
		{
			ActiveHealthBar->AttachedActor = this;
			ActiveHealthBar->AddToViewport();

		}
		
		}
		*/

	/*
	if (Delta < 0.0f)
	{



		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName("Ragdoll");

	}
	*/
	}
}

/*
void AAICharacter::SetTargetActor(AActor* NewTarget)
{

	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject(TargetActorKey, NewTarget);
	}

}
*/
AActor* AAICharacter::GetTargetActor() const 
{

	AMyAIController* AIC = Cast<AMyAIController>(GetController());
	if (AIC) 
	{

		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorKey));

	}

	return nullptr;
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*
* code for restarting AI login
	if (NewHealth == AttributeComp->HealthMax)
	{

		AIC->GetBrainComponent()->StartLogic();
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	}
	*/