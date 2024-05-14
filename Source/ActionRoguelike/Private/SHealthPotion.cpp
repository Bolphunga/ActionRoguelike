// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "Components/StaticMeshComponent.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"



// Sets default values
ASHealthPotion::ASHealthPotion()
{
	HealAmount = 15;

	PotionCooldown = 10.0f;

	bOnCooldown = false;
}

// Interacting with the potion activates it if your health is below 100
// When the potion activates, it becomes invisible and uninteractable and sets a timer that makes the potion usable after 10 seconds
// After the cooldown period, the potion is visible and Interactable again




void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!bOnCooldown)
	{ 
	USAttributeComponent* AttributeComponent = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
	if (AttributeComponent)
	{
		if (AttributeComponent->Health < AttributeComponent->HealthMax)
		{ 
		AttributeComponent->Heal(HealAmount);
		DisablePotion();
		}
	}
	}
}


void ASHealthPotion::DisablePotion()
{
		GetWorldTimerManager().SetTimer(TimerHandle_PotionVisible, this, &ASHealthPotion::EnablePotion, PotionCooldown);
		PotionComp->SetVisibility(false);
		bOnCooldown = true;	
}

void ASHealthPotion::EnablePotion()
{
	PotionComp->SetVisibility(true);
	bOnCooldown = false;
}



// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

