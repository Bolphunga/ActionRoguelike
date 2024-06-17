// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SConsumableBase.h"
#include "SConsumable_Credit.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASConsumable_Credit : public ASConsumableBase
{
	GENERATED_BODY()
	
public:	

	ASConsumable_Credit();

	void Interact_Implementation(APawn* InstigatorPawn);

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Consumables")
	float CreditsAdded;

	//UPROPERTY(ReplicatedUsing = "OnRep_bIsHidden", BlueprintReadOnly)
	bool bIsHidden;

	//UFUNCTION()
	//void OnRep_bIsHidden();

};
