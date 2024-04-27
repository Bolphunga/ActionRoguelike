// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SAttributeComponent.h"


// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up (Blue)

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ASCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &ASCharacter::Teleport);


}

void ASCharacter::PrimaryAttack()

{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.1f);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);

}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(BlackholeProjectile, SpawnTransform, SpawnParams);
}


FVector TeleportLocation;

void ASCharacter::Teleport()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASCharacter::TeleportDestroy, 0.2f);

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

	// Set the TeleportLocation member variable
	GetWorldTimerManager().SetTimer(TimerHandle, [this, Projectile]()
		{
			if (Projectile)
			{
				TeleportLocation = Projectile->GetActorLocation();
			}
		}, 0.2f, false);
}


void ASCharacter::TeleportDestroy()
{
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, TeleportLocation);
	}

	// Set the teleportation timer to call Teleport_TimeElapsed after 0.2 seconds of the particle effect
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASCharacter::Teleport_TimeElapsed, 0.2f);
}

void ASCharacter::Teleport_TimeElapsed()
{

	SetActorLocation(TeleportLocation);
}

void ASCharacter::Jump()
{
	bPressedJump = true;
	JumpKeyHoldTime = 0.0f;
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}




//void ASCharacter::PrimaryAttack_TimeElapsed(UCameraComponent* CameraComponent)
//{
//	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
//	FCollisionObjectQueryParams ObjectQueryParams;
//	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
//	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
//
//	FVector CameraLocation = CameraComponent->GetComponentLocation();
//	FRotator CameraRotation = CameraComponent->GetComponentRotation();
//
//	//GetController()->GetActorEyesViewPoint(CameraLocation, CameraRotation);
//	FVector Target = CameraLocation + (CameraRotation.Vector() * 1000);
//	FHitResult Hit;
//
//	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, Target);
//
//	FTransform SpawnTM = FTransform(LookAtRotation, HandLocation);
//
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	SpawnParams.Instigator = this;
//
//	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, CameraLocation, Target, ObjectQueryParams);
//	DrawDebugLine(GetWorld(), CameraLocation, Target, FColor::Green, false, 2.0f, 0, 2.0f);
//
//	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
//	if (bBlockingHit)
//	{
//		// Print hit location for debugging
//		UE_LOG(LogTemp, Warning, TEXT("Line trace hit location: %s"), *Hit.ImpactPoint.ToString());
//	}
//	else
//	{
//		// Print a message if no hit occurs
//		UE_LOG(LogTemp, Warning, TEXT("Line trace did not hit anything"));
//	}
//}
//
//void ASCharacter::PrimaryAttack_TimeElapsed()
//{
//	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
//
//	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
//
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	SpawnParams.Instigator = this;
//
//	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
//
//	FCollisionObjectQueryParams ObjectQueryParams;
//	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
//	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
//
//	FRotator CameraRotation;
//	FVector CameraLocation;
//
//	GetController()->GetActorEyesViewPoint(CameraLocation, CameraRotation);
//	FVector End = CameraLocation + (CameraRotation.Vector() * 1000);
//
//
//	FHitResult Hit;
//
//	GetWorld()->LineTraceSingleByObjectType(Hit, CameraLocation, End, ObjectQueryParams);
//}