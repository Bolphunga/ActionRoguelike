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

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumables")
	float CreditAmount;
};
