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

	AttackAnimDelay = 0.2f;

	HandSocketname = "Muzzle_01";

	TimeToHitParamName = "TimeToHit";
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

void ASCharacter::HealSelf(float Amount /* = 100*/)
{
	AttributeComp->ApplyHealthChange(this, Amount);
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
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASCharacter::Dash);
	PlayerInputComponent->BindAction("BlackHoleAttack", IE_Pressed, this, &ASCharacter::BlackHoleAttack);
}

void ASCharacter::PrimaryAttack()

{
	StartAttackEffects();

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, AttackAnimDelay);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}

void ASCharacter::BlackHoleAttack()
{
	StartAttackEffects();

	GetWorldTimerManager().SetTimer(TimerHandle_BlackHoleAttack, this, &ASCharacter::BlackHoleAttack_TimeElapsed, AttackAnimDelay);
}

void ASCharacter::BlackHoleAttack_TimeElapsed()
{
	SpawnProjectile(BlackHoleProjectileClass);
	//SetActorLocation(TeleportLocation);
}

void ASCharacter::Dash()
{
	StartAttackEffects();

	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ASCharacter::Dash_TimeElapsed, AttackAnimDelay);
}

void ASCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void ASCharacter::StartAttackEffects()
{	
	PlayAnimMontage(AttackAnim);
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GetMesh(), HandSocketname, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
}


void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	FVector HandLocation = GetMesh()->GetSocketLocation(HandSocketname);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	FCollisionShape Shape;
	Shape.SetSphere(20.0f);

	// Ignore Player
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjParams.AddObjectTypesToQuery(ECC_Pawn);

	FVector TraceStart = CameraComp->GetComponentLocation();

	// Endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
	FVector TraceEnd = TraceStart + (GetControlRotation().Vector() * 5000);
	
	FHitResult Hit;
	if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
	{
		TraceEnd = Hit.ImpactPoint;
	}

	// Find new direction/rotation from hand pointing to impact point in world.
	FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

	FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
	GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
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

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
	}
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}



//void ascharacter::teleportdestroy()
//{
//	if (explosioneffect)
//	{
//		ugameplaystatics::spawnemitteratlocation(getworld(), explosioneffect, teleportlocation);
//	}
//
//	// set the teleportation timer to call teleport_timeelapsed after 0.2 seconds of the particle effect
//	getworldtimermanager().settimer(timerhandle, this, &ascharacter::teleport_timeelapsed, 0.2f);
//}


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