// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_MoveToTarget.h"
#include "Enemies/Enemy_Base.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>

UBTT_MoveToTarget::UBTT_MoveToTarget()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

void UBTT_MoveToTarget::SetOwner(AActor* _pActorOwner)
{
	m_pAIController = Cast<AAIController>(_pActorOwner);
	m_pMySelf = Cast<AEnemy_Base>(m_pAIController->GetPawn());
}

EBTNodeResult::Type UBTT_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* _pNodeMemory)
{
	UBlackboardComponent* pBlackboardComp = OwnerComp.GetBlackboardComponent();
	if (pBlackboardComp)
	{
		AActor* pTarget = Cast<AActor>(pBlackboardComp->GetValueAsObject(m_TargetKey.SelectedKeyName));
		if(pTarget)
		{
			m_pMySelf->Running();
			EPathFollowingRequestResult::Type ResultType = m_pAIController->MoveToActor(pTarget);
			if (ResultType == EPathFollowingRequestResult::AlreadyAtGoal)
			{
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::InProgress;
}

void UBTT_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* pBlackboardComp = OwnerComp.GetBlackboardComponent();
	if (pBlackboardComp)
	{
		AActor* pTarget = Cast<AActor>(pBlackboardComp->GetValueAsObject(m_TargetKey.SelectedKeyName));
		if (pTarget)
		{
			EPathFollowingRequestResult::Type ResultType = m_pAIController->MoveToActor(pTarget);
			if (ResultType == EPathFollowingRequestResult::AlreadyAtGoal)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}
}

EBTNodeResult::Type UBTT_MoveToTarget::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Failed;
}