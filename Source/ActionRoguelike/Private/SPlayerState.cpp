// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include "SAttributeComponent.h"


ASPlayerState::ASPlayerState()
{
	Credits = 0.0f;
	CreditMax = 10000.0f;
	
}

void ASPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();



	//OnCreditChanged.AddDynamic(this, &ASCharacter::OnCreditChanged);
}

//void ASPlayerState::OnCreditChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
//{
//}

bool ASPlayerState::ApplyCreditChange(float Delta)
{
	Credits += Delta;
	Credits = FMath::Clamp(Credits, 0.0f, CreditMax);
	return Delta != 0.0f;
}


