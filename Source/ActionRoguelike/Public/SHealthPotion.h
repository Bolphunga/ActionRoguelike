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

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Consumables")
	float HealAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Consumables")
	float HealthCost;
};
