// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SConsumableBase.h"
#include "SHealthPotion.generated.h"


class UStaticmeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASConsumableBase
{
	GENERATED_BODY()
	
public:	

	ASHealthPotion();

	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumables")
	float HealAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumables")
	float HealthCost;
};
