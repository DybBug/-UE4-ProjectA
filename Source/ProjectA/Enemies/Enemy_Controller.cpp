// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Controller.h"
#include "Enemy_Base.h"
#include "ProjectA_Enums.h"

#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardData.h>
#include <BehaviorTree/BlackboardComponent.h>

AEnemy_Controller::AEnemy_Controller()
{
	bSetControlRotationFromPawnOrientation = false;

	m_TargetKeyName = TEXT("Target");
	m_StateKeyName = TEXT("State");
	m_DestinationKeyName = TEXT("Destination");
	m_DistanceToTargetKeyName = TEXT("DistanceToTarget");
}

void AEnemy_Controller::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	m_pOwner = Cast<AEnemy_Base>(InPawn);

	if (m_pBehaviorTree)
	{		
		UBlackboardComponent* pBlackboardComp;
		UseBlackboard(m_pBehaviorTree->BlackboardAsset, pBlackboardComp);
		if (pBlackboardComp)
		{
			SetStateKey(m_pOwner->GetState());
			SetTargetKey(nullptr);
			SetDestination(FVector::ZeroVector);
			SetDistanceToTarget(0.0f);
			RunBehaviorTree(m_pBehaviorTree);
		}
	}	
}

void AEnemy_Controller::SetStateKey(EEnemy_States _State)
{
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsEnum(m_StateKeyName, (uint8)_State);
	}
}

void AEnemy_Controller::SetTargetKey(AActor* _pTarget)
{
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsObject(m_TargetKeyName, _pTarget);
	}
}

void AEnemy_Controller::SetDestination(const FVector& _Location)
{
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsVector(m_DestinationKeyName, _Location);
	}
}

void AEnemy_Controller::SetDistanceToTarget(float _Distance)
{
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsFloat(m_DistanceToTargetKeyName, _Distance);
	}
}
