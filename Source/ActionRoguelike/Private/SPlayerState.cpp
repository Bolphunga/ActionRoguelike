// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include "SAttributeComponent.h"
#include "Net/UnrealNetwork.h"



ASPlayerState::ASPlayerState()
{
	Credits = 0.0f;
	CreditMax = 10000.0f;

	bReplicates = true;
}


bool ASPlayerState::ApplyCreditChange(int32 Delta)
{
	Credits += Delta;
	Credits = FMath::Clamp(Credits, 0.0f, CreditMax);
	MulticastCreditChanged(this, Credits, Delta);
	
	return Delta != 0.0f;
}

void ASPlayerState::MulticastCreditChanged_Implementation(ASPlayerState* PlayerState, float NewCredits, float Delta)
{
	OnCreditChanged.Broadcast(PlayerState, NewCredits, Delta);
}

int32 ASPlayerState::GetCredits() const
{
	return Credits;
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPlayerState, Credits);
	DOREPLIFETIME(ASPlayerState, CreditMax);
}