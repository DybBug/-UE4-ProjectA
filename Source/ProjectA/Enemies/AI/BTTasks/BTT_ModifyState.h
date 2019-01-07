// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ModifyState.generated.h"

/**
 * 
 */
class AEnemy_Base;
enum class EEnemy_States : uint8;

UCLASS()
class PROJECTA_API UBTT_ModifyState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_ModifyState();

private:
	virtual void SetOwner(AActor* ActorOwner) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private :
	UPROPERTY()
	AEnemy_Base* m_pMySelf;

	UPROPERTY(EditAnywhere)
	EEnemy_States m_State;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector m_StateKey;
};
