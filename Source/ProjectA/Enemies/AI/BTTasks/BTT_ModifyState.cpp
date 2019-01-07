// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_ModifyState.h"
#include "Enemies/Enemy_Base.h"

#include <BehaviorTree/BlackboardComponent.h>

UBTT_ModifyState::UBTT_ModifyState()
{
	bCreateNodeInstance = true;
}

void UBTT_ModifyState::SetOwner(AActor* ActorOwner)
{
	AController* pController = Cast<AController>(ActorOwner);
	m_pMySelf = Cast<AEnemy_Base>(pController->GetPawn());
}

EBTNodeResult::Type UBTT_ModifyState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	m_pMySelf->ModifyState(m_State);
	return EBTNodeResult::Succeeded;
}

