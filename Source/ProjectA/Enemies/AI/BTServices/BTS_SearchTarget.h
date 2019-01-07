// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_SearchTarget.generated.h"

class AEnemy_Base;
/**
 * 타겟(플레이어)를 찾고 찾음.
 */

UCLASS()
class PROJECTA_API UBTS_SearchTarget : public UBTService
{
	GENERATED_BODY()

public :
	UBTS_SearchTarget();

protected :
	virtual void SetOwner(AActor* ActorOwner) override;

protected :
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private :
	UPROPERTY()
	AEnemy_Base* m_pMySelf;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector m_TargetKey;	
};
