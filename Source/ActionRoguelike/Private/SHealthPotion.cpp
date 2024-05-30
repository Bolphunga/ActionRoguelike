// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "Components/StaticMeshComponent.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"



// Sets default values
ASHealthPotion::ASHealthPotion()
{
	HealAmount = 15;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (!bOnCooldown)
	{ 
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttributeComp)
	{
		if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
		{ 
		AttributeComp->ApplyHealthChange(this, HealAmount);
		HideConsumable();
		}
	}
	}
}
