// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SConsumableBase.h"
#include "SHealthPotion.generated.h"


UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASConsumableBase
{
	GENERATED_BODY()
	
public:	

	void Interact_Implementation(APawn* InstigatorPawn);

	bool bOnCooldown;

	// Sets default values for this actor's properties
	ASHealthPotion();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumables")
	float HealAmount;

	FTimerHandle TimerHandle_PotionVisible;

	float PotionCooldown;

	void DisablePotion();

	void EnablePotion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
