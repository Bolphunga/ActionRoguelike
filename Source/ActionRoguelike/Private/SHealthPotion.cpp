// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "Components/StaticMeshComponent.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"
#include "SPlayerState.h"



// Sets default values
ASHealthPotion::ASHealthPotion()
{
	HealAmount = 15.f;
	HealthCost = -15.f;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (!bOnCooldown)

	{ 
		ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>();
		if (PS && PS->GetCredits() >= -HealthCost)
		{
			USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
				if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
				{ 
					AttributeComp->ApplyHealthChange(this, HealAmount);

					HideConsumable();
				}
				PS->ApplyCreditChange(HealthCost);
		}
	}
}
