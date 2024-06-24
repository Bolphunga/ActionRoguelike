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

	UPROPERTY(EditAnywhere, Category = "Consumables")
	float ItemCooldown;

	void ShowConsumable();

	void HideConsumable();

	UFUNCTION(BlueprintCallable)
	bool IsVisible() const;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Consumables")
	UStaticMeshComponent* MeshComp;

	FTimerHandle TimerHandle_ItemVisible;

	UPROPERTY(ReplicatedUsing = "OnRep_IsVisible", BlueprintReadOnly)
	bool bIsVisible;

	UFUNCTION()
	void OnRep_IsVisible();
};
