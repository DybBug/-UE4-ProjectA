// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MoveToTarget.generated.h"

class AEnemy_Base;
class AAIController;

/**
 * 타겟의 위치로 이동.
 */
UCLASS()
class PROJECTA_API UBTT_MoveToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public :
	UBTT_MoveToTarget();

private :
	virtual void SetOwner(AActor* _pActorOwner) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* _pNodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected :
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private :
	UPROPERTY()
	AEnemy_Base* m_pMySelf;

	UPROPERTY()
	AAIController* m_pAIController;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector m_TargetKey;

};

