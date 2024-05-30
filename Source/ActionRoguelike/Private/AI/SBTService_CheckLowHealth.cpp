// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "AI/SAICharacter.h"
#include "SAttributeComponent.h"



void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	

			APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
			if (ensure(AIPawn))
			{
				USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AIPawn);
				if (ensure(AttributeComp))
				{
					bool bIsLowHealth = AttributeComp->GetHealth() <= 30.f;

					UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
					BlackBoardComp->SetValueAsBool(HealthLevelKey.SelectedKeyName, bIsLowHealth);
					float MinionCurrentHealth =  AttributeComp->Health;

					UE_LOG(LogTemp, Log, TEXT("MinionCurrentHealth"));
				}
			}
}
