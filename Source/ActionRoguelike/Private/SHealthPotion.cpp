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

}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComponent = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
	if (AttributeComponent)
	{
		if (AttributeComponent->Health < 100)
		{ 
		AttributeComponent->Heal(HealAmount);
		Potion_Disabled();
		}
	}
	
}



void ASHealthPotion::Potion_Disabled()
{
		GetWorldTimerManager().SetTimer(TimerHandle_PotionVisible, this, &ASHealthPotion::Potion_Enabled, PotionCooldown);
		PotionComp->SetVisibility(false);

}

void ASHealthPotion::Potion_Enabled()
{
	PotionComp->SetVisibility(true);
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

