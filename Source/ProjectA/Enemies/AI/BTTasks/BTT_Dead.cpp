// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_Dead.h"
#include "Enemies/Enemy_Base.h"
#include "Players/Player_Character.h"

#include <AIController.h>


UBTT_Dead::UBTT_Dead()
{
	bCreateNodeInstance = true;
}

void UBTT_Dead::SetOwner(AActor* ActorOwner)
{
	AAIController* pController = Cast<AAIController>(ActorOwner);
	m_pMySelf = Cast<AEnemy_Base>(pController->GetPawn());
}

EBTNodeResult::Type UBTT_Dead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const FEnemy_Info& Info = m_pMySelf->GetInfo();
	m_pMySelf->GetInteractionUser()->GainExperience(Info.ExperienceToAcquire);

	m_pMySelf->UnInteract();
	m_pMySelf->SetActorEnableCollision(false);
	m_pMySelf->DropChest();
	m_pMySelf->Respawn();

	return EBTNodeResult::InProgress;
}
