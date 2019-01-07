// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_CalculateDistance.generated.h"

class AEnemy_Base;
/**
 * 타겟과의 거리 계산 하기.
 */
UCLASS()
class PROJECTA_API UBTS_CalculateDistance : public UBTService
{
	GENERATED_BODY()

public:
	UBTS_CalculateDistance();

private:
	virtual void SetOwner(AActor* _pActorOwner) override;

protected :
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private :
	float _CalculateDistance(AActor* _pTarget);

private :
	UPROPERTY()
	AEnemy_Base* m_pMySelf;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector m_TargetKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector m_DistanceKey;	
};
