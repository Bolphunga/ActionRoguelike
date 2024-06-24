// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

class USSaveGame;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Consumable")
	int32 CreditMax;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(USSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(USSaveGame* SaveObject);

protected:

	ASPlayerState();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_Credits", Category = "Consumable")
	int32 Credits;

	// OnRep_ can use a paramater that uses the old value of the variable it is bound to. Very useful in this case to figure out the delta.
	UFUNCTION()
	void OnRep_Credits(int32 OldCredits);

	//UFUNCTION(NetMulticast, Reliable) //@Fixme: Mark as Unreliable once we move the 'state' of our SCharacter.
	//void MulticastCreditChanged(ASPlayerState* PlayerState, float NewCredits, float Delta);
};
