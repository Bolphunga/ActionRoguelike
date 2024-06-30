// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

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

	if (bIsVisible)
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

FText ASHealthPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttributeComp && AttributeComp->IsFullHealth())
	{
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at Full Health");
	}
	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Costs {0} Credits. Restores {1} Health Points."), -HealthCost, HealAmount);
}

#undef LOCTEXT_NAMESPACE