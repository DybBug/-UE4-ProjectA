// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_Attack.h"
#include "Enemies/Enemy_Base.h"
#include "Skills/Skill_Base.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <Animation/AnimMontage.h>
#include <TimerManager.h>

UBTT_Attack::UBTT_Attack()
{
	bCreateNodeInstance = true;
}

void UBTT_Attack::SetOwner(AActor* ActorOwner)
{
	AController* pController = Cast<AController>(ActorOwner);
	m_pMySelf = Cast<AEnemy_Base>(pController->GetPawn());
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	float Duration = m_pMySelf->UseSkillBy(m_SkillClass);

	m_pMySelf->GetMovementComponent()->Deactivate();

	UBlackboardComponent* pBlackboardComp = OwnerComp.GetBlackboardComponent();
	if (pBlackboardComp)
	{
		FTimerHandle hTimer;
		GetWorld()->GetTimerManager().SetTimer(hTimer, [&]() {
			m_pMySelf->GetMovementComponent()->Activate();
			GetWorld()->GetTimerManager().ClearTimer(hTimer);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}, Duration, false);
	}
	return EBTNodeResult::InProgress;
}


