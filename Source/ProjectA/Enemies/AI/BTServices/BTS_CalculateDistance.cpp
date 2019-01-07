// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_CalculateDistance.h"
#include "Enemies/Enemy_Base.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>

UBTS_CalculateDistance::UBTS_CalculateDistance()
{
	bCreateNodeInstance = true;
	//bNotifyOnSearch = true;
}

void UBTS_CalculateDistance::SetOwner(AActor* _pActorOwner)
{
	AAIController* pController = Cast<AAIController>(_pActorOwner);
	m_pMySelf = Cast<AEnemy_Base>(pController->GetPawn());
}

void UBTS_CalculateDistance::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	if (m_pMySelf)
	{
		UBlackboardComponent* pBlackbordComp = SearchData.OwnerComp.GetBlackboardComponent();
		if (pBlackbordComp)
		{
			AActor* pTarget = Cast<AActor>(pBlackbordComp->GetValueAsObject(m_TargetKey.SelectedKeyName));
			float Distance = _CalculateDistance(pTarget);

			pBlackbordComp->SetValueAsFloat(m_DistanceKey.SelectedKeyName, Distance);
		}
	}
}

void UBTS_CalculateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (m_pMySelf)
	{
		UBlackboardComponent* pBlackbordComp = OwnerComp.GetBlackboardComponent();
		if (pBlackbordComp)
		{
			AActor* pTarget = Cast<AActor>(pBlackbordComp->GetValueAsObject(m_TargetKey.SelectedKeyName));
			float Distance = _CalculateDistance(pTarget);

			pBlackbordComp->SetValueAsFloat(m_DistanceKey.SelectedKeyName, Distance);
		}
	}
}

float UBTS_CalculateDistance::_CalculateDistance(AActor* _pTarget)
{
	FVector Direction = m_pMySelf->GetActorLocation() - _pTarget->GetActorLocation();
	float Distance = Direction.Size();

	return Distance;
}

