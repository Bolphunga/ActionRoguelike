// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect_Thorns.h"
#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"


USActionEffect_Thorns::USActionEffect_Thorns()
{
	ReflectedFraction = 0.2f;

	Duration = 0.0f;
	Period = 0.0f;
}

void USActionEffect_Thorns::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Instigator);
	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.AddDynamic(this, &USActionEffect_Thorns::OnHealthChanged);
	}

}

void USActionEffect_Thorns::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Instigator);
	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.RemoveDynamic(this, &USActionEffect_Thorns::OnHealthChanged);
	}

}

void USActionEffect_Thorns::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	AActor* OwningActor = OwningComp->GetOwner();

	// Damage only.
	if (Delta < 0.0f && InstigatorActor != OwningActor)
	{
		int32 ReflectedAmount = FMath::RoundToInt(Delta * ReflectedFraction);
		if (ReflectedAmount == 0)
		{
			return;
		}

		// Flip to positive so we don't heal ourselves
		ReflectedAmount = FMath::Abs(ReflectedAmount);

		// Return damage to the instigator
		USGameplayFunctionLibrary::ApplyDamage(InstigatorActor, OwningActor, ReflectedAmount);
	}
}