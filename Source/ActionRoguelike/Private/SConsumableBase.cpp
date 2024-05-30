// Fill out your copyright notice in the Description page of Project Settings.


#include "SConsumableBase.h"

// Sets default values
ASConsumableBase::ASConsumableBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionProfileName("Consumable");
	RootComponent = MeshComp;

	ItemCooldown = 10.0f;

	bOnCooldown = false;
}

void ASConsumableBase::Interact_Implementation(APawn* InstigatorPawn)
{
	// Shared logic here
}

void ASConsumableBase::HideConsumable()
{
	FTimerHandle TimerHandle_ItemVisible;
	GetWorldTimerManager().SetTimer(TimerHandle_ItemVisible, this, &ASConsumableBase::ShowConsumable, ItemCooldown);
	RootComponent->SetVisibility(false);
	bOnCooldown = true;
}

void ASConsumableBase::ShowConsumable()
{
	RootComponent->SetVisibility(true);
	bOnCooldown = false;
}