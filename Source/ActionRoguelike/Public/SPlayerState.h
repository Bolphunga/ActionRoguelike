// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreditChanged, AActor*, InstigatorActor, ASPlayerState*, OwningComp, float, NewCredits, float, Delta);

UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	ASPlayerState();

	//UPROPERTY(BlueprintAssignable)
	//FOnCreditChanged OnCreditChanged;

	bool ApplyCreditChange(float Delta);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumable")
	float Credits;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumable")
	float CreditMax;

protected:

	virtual void PostInitializeComponents() override;


	//UFUNCTION()
	//void OnCreditChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
};
