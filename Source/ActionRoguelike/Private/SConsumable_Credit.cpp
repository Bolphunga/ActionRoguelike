// Fill out your copyright notice in the Description page of Project Settings.


#include "SConsumable_Credit.h"
#include "SPlayerState.h"
#include "Net/UnrealNetwork.h"




ASConsumable_Credit::ASConsumable_Credit()
{
	CreditsAdded = 15;
}



void ASConsumable_Credit::Interact_Implementation(APawn* InstigatorPawn)
{
		if (!ensure(InstigatorPawn))
		{
			return;
		}

		if (bIsVisible)

		{
			ASPlayerState* PS = Cast<ASPlayerState>(InstigatorPawn->GetPlayerState<APlayerState>());
			if (PS)
			{
				PS->ApplyCreditChange(CreditsAdded);
				HideConsumable();

				UE_LOG(LogTemp, Log, TEXT("Credits Added: %f"), PS->GetCredits());
			}
		}
}

void ASConsumable_Credit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASConsumable_Credit, CreditsAdded);
}

