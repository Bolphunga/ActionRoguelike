// Fill out your copyright notice in the Description page of Project Settings.


#include "SConsumable_Credit.h"



ASConsumable_Credit::ASConsumable_Credit()
{
	CreditAmount = 15;
}



void ASConsumable_Credit::Interact_Implementation(APawn* InstigatorPawn)
{
		if (!ensure(InstigatorPawn))
		{
			return;
		}
}
