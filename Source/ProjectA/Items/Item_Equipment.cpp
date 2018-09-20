// Fill out your copyright notice in the Description page of Project Settings.
#include "Item_Equipment.h"
#include "ProjectA.h"
#include "Components/Component_Equipment.h"
#include "Components/Component_Inventory.h"
#include "Components/Component_Stat.h"
#include "Players/Player_Character.h"
#include "Enemies/Enemy_Base.h"

#include <Components/ArrowComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/DamageType.h>


AItem_Equipment::AItem_Equipment()
{
	m_pArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = m_pArrow;

	m_pCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	m_pCollision->SetCollisionObjectType(UEngineTypes::ConvertToCollisionChannel(OTQ_Equipment));
	m_pCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pCollision->SetCollisionResponseToChannel(UEngineTypes::ConvertToCollisionChannel(OTQ_Player), ECollisionResponse::ECR_Ignore);
	m_pCollision->SetCollisionResponseToChannel(UEngineTypes::ConvertToCollisionChannel(OTQ_Enemy), ECollisionResponse::ECR_Overlap);
	m_pCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem_Equipment::_OnComponentBeginOverlap);
	m_pCollision->SetupAttachment(RootComponent);

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetupAttachment(RootComponent);
}

void AItem_Equipment::InitItem(AActor* _pOwner)
{
	AItem_Base::InitItem(_pOwner);
}

bool AItem_Equipment::OnUse(FInventorySlot_Info* const pSlotInfo)
{
	if (m_pPlayer)
	{
		pSlotInfo->pItem = nullptr;
		pSlotInfo->Amount = 0;
		return m_pPlayer->GetEquipment()->OnEquip(this);
	}

	return false;
}

void AItem_Equipment::StartAttack()
{
	m_pCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AItem_Equipment::EndAttack()
{
	m_pCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItem_Equipment::_OnComponentBeginOverlap(
	UPrimitiveComponent* _pOverlappedComponent,
	AActor* _pOtherActor,
	UPrimitiveComponent* _pOtherComp,
	int32 _OtherBodyIndex,
	bool _bFromSweep,
	const FHitResult& _SweepResult)
{
	AEnemy_Base* pEnemy = Cast<AEnemy_Base>(_pOtherActor);
	if (pEnemy)
	{
		const FStat_Info& StatInfo = m_pPlayer->GetStat()->GetStat(EStat_Types::Attack);		
		FDamageEvent DamageEvent(UDamageType::StaticClass());
		pEnemy->TakeDamage(StatInfo.CurrentValue, DamageEvent, m_pPlayer->GetController(), this);
	}
}


