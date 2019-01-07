// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Attack.generated.h"

/**
 * 
 */
class UAnimMontage;
class AEnemy_Base;
class ASkill_Base;
class UAnimMontage;

UCLASS()
class PROJECTA_API UBTT_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public :
	UBTT_Attack();

private :
	virtual void SetOwner(AActor* ActorOwner) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private :
	UPROPERTY()
	AEnemy_Base* m_pMySelf;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASkill_Base> m_SkillClass;
};
