// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, NewPawn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, APlayerState*, NewPlayerState);

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY()
	UUserWidget* PauseMenuInstance;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void TogglePauseMenu();

	void SetupInputComponent() override;

	UPROPERTY(BlueprintAssignable)
	FOnPawnChanged OnPawnChanged;

	// Listen for upcoming PlayerState (For clients this might be nullptr when initially joining a game,
	// afterwards, playerstate will not change again as PlayerControllers maintain the same PlayerState throughout the level)
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateChanged OnPlayerStateRecieved;

	void SetPawn(APawn* InPawn) override;

	// Called when PlayerController is ready to beging playing. A good time to initialize things like UI, which might be too early
	// in BeginPlay() (especially in multiplayer clients where not all data such as PlayerState may not be recieved yet)
	void BeginPlayingState() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerController")
	void BlueprintBeginPlayingState();

	void OnRep_PlayerState() override;
};
