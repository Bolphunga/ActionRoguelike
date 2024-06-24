// Fill out your copyright notice in the Description page of Project Settings.


#include "SConsumableBase.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ASConsumableBase::ASConsumableBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionProfileName("Consumable");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	ItemCooldown = 10.0f;
	bIsVisible = true;

	bReplicates = true;
}

void ASConsumableBase::Interact_Implementation(APawn* InstigatorPawn)
{
	// Shared logic here
}

void ASConsumableBase::HideConsumable()
{
	bIsVisible = false;
	OnRep_IsVisible();

	GetWorldTimerManager().SetTimer(TimerHandle_ItemVisible, this, &ASConsumableBase::ShowConsumable, ItemCooldown);
}

void ASConsumableBase::ShowConsumable()
{
	bIsVisible = true;
	OnRep_IsVisible();
}

void ASConsumableBase::OnRep_IsVisible()
{
	RootComponent->SetVisibility(bIsVisible, true);
	SetActorEnableCollision(bIsVisible);
}


bool ASConsumableBase::IsVisible() const
{
	return bIsVisible;
}

void ASConsumableBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASConsumableBase, bIsVisible);
}
