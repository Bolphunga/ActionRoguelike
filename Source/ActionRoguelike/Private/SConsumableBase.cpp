// Fill out your copyright notice in the Description page of Project Settings.


#include "SConsumableBase.h"

// Sets default values
ASConsumableBase::ASConsumableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PotionComp = CreateDefaultSubobject<UStaticMeshComponent>("PotionComp");
}

// Called when the game starts or when spawned
void ASConsumableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASConsumableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

