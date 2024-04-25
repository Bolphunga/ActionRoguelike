// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine\RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrelComp = CreateDefaultSubobject<UStaticMeshComponent>("BarrelComp");
	BarrelComp->SetSimulatePhysics(true);
	RootComponent = BarrelComp;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(BarrelComp);
	
	RadialForce->SetAutoActivate(true);

	RadialForce->Radius = 750.0f;
	RadialForce->ImpulseStrength = 2500.0f;
	//Optional, ignores mass of other objects (if set to false, ImpulseStrenth will need to be much higher to push most objects, depending on their mass)
	RadialForce->bImpulseVelChange = true;

	//Optional, default constructor of the component already adds 4 object types to effect, excluding WorldDynamic
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);

	//Binding either in constructor or in PostInitializeComponents() below
	//BarrelComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit)

}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	BarrelComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForce->FireImpulse();
	
	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	//%s String
	//%f Float
	//logs: "OtherActor: MyActor_1, at game time: 124.4"
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);


	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

