// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SunActions.generated.h"



class USunActionComponent;
class UWorld;
class GameplayTagContainer;

/**
 * 
 */
UCLASS(Blueprintable)
class FIRST5_5_API USunActions : public UObject
{
	GENERATED_BODY()

public:

	

	UPROPERTY()
	TObjectPtr<USunActionComponent> ActionComp;

	UPROPERTY()
	TArray<TSubclassOf<USunActions>> NewAction;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;
	
	UPROPERTY()
	bool isRunning;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool autoStart;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool BisRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	USunActionComponent* GetOwningComponent() const;
	
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	// Action nickname to start/stop without a reference to the object
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UWorld* GetWorld() const override;
};
