// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include "SAttributeComponent.h"



ASPlayerState::ASPlayerState()
{
	Credits = 0.0f;
	CreditMax = 10000.0f;
}

bool ASPlayerState::ApplyCreditChange(int32 Delta)
{
	Credits += Delta;
	Credits = FMath::Clamp(Credits, 0.0f, CreditMax);

	OnCreditChanged.Broadcast(this, Credits, Delta);
	return Delta != 0.0f;
}


int32 ASPlayerState::GetCredits() const
{
	return Credits;
}