// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Engine/DataTable.h"
#include "SGameModeBase.generated.h"

class UEnvQueryInstanceBlueprintWrapper;
class UEnvQuery;
class UCurveFloat;
class USSaveGame;
class USMonsterData;


// Data table row for spawning monsters in game mode
USTRUCT(BlueprintType)
struct FMonsterInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	public:
	
		FMonsterInfoRow()
		{
			Weight = 1.0f;
			SpawnCost = 5.0f;
			KillReward = 15.0f;
		}

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FPrimaryAssetId MonsterId;
		//USMonsterData* MonsterData;
		//TSubclassOf<AActor> MonsterClass;

		// Relative chance to pick this monster
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Weight;

		// Points required by the game mode to spawn this unit
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float SpawnCost;

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float KillReward;
};
/**
 * 
 */

UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	FString SlotName;

	UPROPERTY()
	USSaveGame* CurrentSaveGame;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UDataTable* MonsterTable;

	//UPROPERTY(EditDefaultsOnly, Category = "AI")
	//TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	void OnMonsterLoaded(FPrimaryAssetId LoadedId, FVector SpawnLocation);
	
	UFUNCTION()
	void RespawnTimerElapsed(AController* Controller);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consumables")
	float CreditsAdded;

public:

	ASGameModeBase();

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	virtual void StartPlay();

	UFUNCTION(Exec)
	void KillAll();

	UFUNCTION(BlueprintCallable)
	void WriteSaveGame();

	void LoadSaveGame();
};
