// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Credits")
	int32 GetCredits() const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCreditsChanged OnCreditChanged;

	bool ApplyCreditChange(int32 Delta);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumable")
	int32 CreditMax;

protected:

	ASPlayerState();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumable")
	int32 Credits;
};
