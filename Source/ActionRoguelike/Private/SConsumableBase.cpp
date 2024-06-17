// Fill out your copyright notice in the Description page of Project Settings.


#include "SConsumableBase.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ASConsumableBase::ASConsumableBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionProfileName("Consumable");
	RootComponent = MeshComp;

	ItemCooldown = 10.0f;

	bIsVisible = true;

	bReplicates = true;
}

void ASConsumableBase::Interact_Implementation(APawn* InstigatorPawn)
{
	// Shared logic here
}

//void ASConsumableBase::HideConsumable()
//{
//	ServerHideConsumable();
//}

void ASConsumableBase::HideConsumable()
{
	OnRep_IsVisible();
}

void ASConsumableBase::ShowConsumable()
{
	bIsVisible = true;
	RootComponent->SetVisibility(bIsVisible);
}

void ASConsumableBase::OnRep_IsVisible()
{
	if (bIsVisible)
	{
		FTimerHandle TimerHandle_ItemVisible;
		GetWorldTimerManager().SetTimer(TimerHandle_ItemVisible, this, &ASConsumableBase::ShowConsumable, ItemCooldown);
		
		bIsVisible = false;
		RootComponent->SetVisibility(bIsVisible);
	}
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
