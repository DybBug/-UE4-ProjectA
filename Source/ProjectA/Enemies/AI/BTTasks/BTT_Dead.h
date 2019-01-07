// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Dead.generated.h"

class AEnemy_Base;
/**
 * 
 */
UCLASS()
class PROJECTA_API UBTT_Dead : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_Dead();

private:
	virtual void SetOwner(AActor* ActorOwner) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private :
	UPROPERTY()
	AEnemy_Base* m_pMySelf;
	
	
};
