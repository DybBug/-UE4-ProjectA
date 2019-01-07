// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_LookAtTarget.generated.h"

class AEnemy_Base;

/**
 * 
 * 타겟(플레이어)를 바라본다.
 */
UCLASS()
class PROJECTA_API UBTS_LookAtTarget : public UBTService
{
	GENERATED_BODY()

public:
	UBTS_LookAtTarget();

private:
	virtual void SetOwner(AActor* _pActorOwner) override;

protected :
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private :
	void _LookAtTarget(AActor* _pTarget);

private :
	UPROPERTY()
	AEnemy_Base* m_pMySelf;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector m_TargetKey;	
};
