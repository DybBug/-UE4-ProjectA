// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_SearchTarget.h"
#include "Enemies/Enemy_Base.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>

UBTS_SearchTarget::UBTS_SearchTarget()
{
	bCreateNodeInstance = true;
}

void UBTS_SearchTarget::SetOwner(AActor* ActorOwner)
{
	if (AController* pController = Cast<AController>(ActorOwner))
	{
		m_pMySelf = Cast<AEnemy_Base>(pController->GetPawn());
	}
}

void UBTS_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* pPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (pPlayer)
	{
		FVector MyLocation = m_pMySelf->GetActorLocation();
		FVector PlayerLocation = pPlayer->GetActorLocation();

		float TargetDistance = FVector::Distance(PlayerLocation, MyLocation);
		float SearchRange = m_pMySelf->GetSerachRange();
		if (TargetDistance <= SearchRange)
		{
			FVector Forward = m_pMySelf->GetActorForwardVector();
			Forward.Z = 0;
			Forward.Normalize();

			FVector Direction = (PlayerLocation - MyLocation);
			Direction.Z = 0;
			Direction.Normalize();

			float Angle = FMath::Acos(FVector::DotProduct(Forward, Direction));
			Angle = FMath::RadiansToDegrees(Angle);

			if (FMath::Abs(Angle) <= (m_pMySelf->GetInfo().AngleOfView/2.f))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(m_TargetKey.SelectedKeyName, pPlayer);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(m_TargetKey.SelectedKeyName, nullptr);
}

