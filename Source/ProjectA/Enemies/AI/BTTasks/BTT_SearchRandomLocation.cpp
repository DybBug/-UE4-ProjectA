// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_SearchRandomLocation.h"
#include "Enemies/Enemy_Base.h"

#include <NavigationSystem.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTT_SearchRandomLocation::UBTT_SearchRandomLocation()
{
	bCreateNodeInstance = true;
}

void UBTT_SearchRandomLocation::SetOwner(AActor* ActorOwner)
{
	AController* pController = Cast<AController>(ActorOwner);
	m_pMySelf = Cast<AEnemy_Base>(pController->GetPawn());
}

EBTNodeResult::Type UBTT_SearchRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector RandomLocation;
	if (UNavigationSystemV1::K2_GetRandomPointInNavigableRadius(this, m_pMySelf->GetActorLocation(), RandomLocation, 1000.f))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(m_RandomLocationKey.SelectedKeyName, RandomLocation);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
