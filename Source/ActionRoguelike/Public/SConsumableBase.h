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
	// Sets default values for this actor's properties
	ASConsumableBase();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Consumables")
	UStaticMeshComponent* PotionComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
