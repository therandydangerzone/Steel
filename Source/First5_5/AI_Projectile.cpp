// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "AICharacter.h"
#include "SunActionComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "SQLBPFunctionLib.h"

// Sets default values
AAI_Projectile::AAI_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
	
	//ProjectileComp = CreateDefaultSubobject<UNiagaraSystem>("ProjectileComp");
	//EffectComp = CreateDefaultSubobject<UNiagaraComponent>("EffectComp");
	//EffectComp->SetupAttachment(SphereComp);

	

	//ProjectileComp = CreateDefaultSubobject<UNiagaraSystem>("ProjectileComp");
	

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 2000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	DamageAmount = 5.0f;
	DelayDuration = .5f;
}

// Called when the game starts or when spawned
void AAI_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AAI_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAI_Projectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAI_Projectile::OnActorOverLap);
	SphereComp->OnComponentHit.AddDynamic(this, &AAI_Projectile::OnActorHit);
}

void AAI_Projectile::OnActorOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	if (OtherActor && OtherActor != GetInstigator() && OtherActor->ActorHasTag(PlayerTag))
	{

		USunActionComponent* ActionComp = Cast<USunActionComponent>(OtherActor->GetComponentByClass(USunActionComponent::StaticClass()));
		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{

			MovementComp->Velocity = -MovementComp->Velocity;
			SetInstigator(Cast<APawn>(OtherActor));
			return;
			
		}


	}


	
	if (OtherActor && OtherActor != GetInstigator() && OtherActor->ActorHasTag(PlayerTag) || OtherActor->ActorHasTag(AITag))
	{
		
	BisHit = true;
	FVector SpawnScale = FVector(1.0f, 1.0f, 1.0f);

		//USQLBPFunctionLib

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		USQLBPFunctionLib::ApplyDamage(GetInstigator(), OtherActor, DamageAmount);
		
		UGameplayStatics::SpawnSoundAtLocation(this, OnHitSound, GetActorLocation(), FRotator::ZeroRotator);

		UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, EffectComp, GetActorLocation(), FRotator::ZeroRotator, SpawnScale, true, true, ENCPoolMethod::AutoRelease);

			//AActor* ExplosionNiagara = GetWorld()->SpawnActor<AActor>(Explosion, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), Params);
			//Explode();
			//GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AAI_Projectile::OnDelayElapsed, DelayDuration, false);
		Destroy();
			
		
		

	}
	
	if (OtherActor && OtherActor != GetInstigator() && OtherActor->ActorHasTag(LandscapeTag))
	{

		BisHit = true;
		FVector SpawnScale = FVector(1.0f, 1.0f, 1.0f);

		//USQLBPFunctionLib

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//USQLBPFunctionLib::ApplyDamage(GetInstigator(), OtherActor, DamageAmount);

		UGameplayStatics::SpawnSoundAtLocation(this, OnHitSound, GetActorLocation(), FRotator::ZeroRotator);

		UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, EffectComp, GetActorLocation(), FRotator::ZeroRotator, SpawnScale, true, true, ENCPoolMethod::AutoRelease);

		//AActor* ExplosionNiagara = GetWorld()->SpawnActor<AActor>(Explosion, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), Params);
		//Explode();
		//GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AAI_Projectile::OnDelayElapsed, DelayDuration, false);
		Destroy();




	}
	/*
	if (OverlappedComponent)
	{
		BisHit = true;
		FVector SpawnScale = FVector(1.0f, 1.0f, 1.0f);

		//USQLBPFunctionLib

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//USQLBPFunctionLib::ApplyDamage(GetInstigator(), OtherActor, DamageAmount);

		UGameplayStatics::SpawnSoundAtLocation(this, OnHitSound, GetActorLocation(), FRotator::ZeroRotator);

		UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, EffectComp, GetActorLocation(), FRotator::ZeroRotator, SpawnScale, true, true, ENCPoolMethod::AutoRelease);

		//AActor* ExplosionNiagara = GetWorld()->SpawnActor<AActor>(Explosion, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), Params);
		//Explode();
		//GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AAI_Projectile::OnDelayElapsed, DelayDuration, false);
		Destroy();


	}
	//BisHit = false;
	*/
}

void AAI_Projectile::OnDelayElapsed()
{

	UE_LOG(LogTemp, Warning, TEXT("Delay for destroying explosion projectile niagara worked!"));
	GetWorldTimerManager().ClearTimer(DelayTimerHandle);

	Destroy();
}



void AAI_Projectile::Explode_Implementation()
{

	
	

}


void AAI_Projectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	

	
}
