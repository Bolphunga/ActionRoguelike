// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "SGameplayInterface.h"
#include "SConsumableBase.generated.h"


class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASConsumableBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	
	ASConsumableBase();

	void Interact_Implementation(APawn* InstigatorPawn);

	bool bOnCooldown;

	UPROPERTY(EditAnywhere, Category = "Consumables")
	float ItemCooldown;

	void ShowConsumable();

	void HideConsumable();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Consumables")
	UStaticMeshComponent* MeshComp;
};
