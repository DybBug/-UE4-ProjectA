// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_LookAtTarget.h"
#include "Enemies/Enemy_Base.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>


UBTS_LookAtTarget::UBTS_LookAtTarget()
{
	bCreateNodeInstance = true;
}

void UBTS_LookAtTarget::SetOwner(AActor* _pActorOwner)
{
	AAIController* pController = Cast<AAIController>(_pActorOwner);
	m_pMySelf = Cast<AEnemy_Base>(pController->GetPawn());
}

void UBTS_LookAtTarget::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	if (m_pMySelf)
	{
		UBlackboardComponent* pBlackboardComp = SearchData.OwnerComp.GetBlackboardComponent();
		if (pBlackboardComp)
		{
			AActor* pTarget = Cast<AActor>(pBlackboardComp->GetValueAsObject(m_TargetKey.SelectedKeyName));
			if (pTarget)
			{
				_LookAtTarget(pTarget);
			}
		}
	}
}


void UBTS_LookAtTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (m_pMySelf)
	{
		UBlackboardComponent* pBlackboardComp = OwnerComp.GetBlackboardComponent();
		if (pBlackboardComp)
		{
			AActor* pTarget = Cast<AActor>(pBlackboardComp->GetValueAsObject(m_TargetKey.SelectedKeyName));
			if (pTarget)
			{
				_LookAtTarget(pTarget);
			}
		}
	}
}

void UBTS_LookAtTarget::_LookAtTarget(AActor* _pTarget)
{
	FVector TargetLocation = _pTarget->GetActorLocation();
	FVector TargetDirection = (TargetLocation - m_pMySelf->GetActorLocation());

	float YawAngle = FMath::RadiansToDegrees(FMath::Atan2(TargetDirection.Y, TargetDirection.X));

	FRotator ActorRot = m_pMySelf->GetControlRotation();
	ActorRot.Yaw = YawAngle;

	m_pMySelf->GetController()->SetControlRotation(ActorRot);
}

