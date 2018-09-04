// Fill out your copyright notice in the Description page of Project Settings.
#include "Item_Equipment.h"
#include "ProjectA.h"
#include "Components/Component_Equipment.h"
#include "Components/Component_Inventory.h"
#include "Players/Player_Character.h"

#include <Components/ArrowComponent.h>
#include <Components/StaticMeshComponent.h>



AItem_Equipment::AItem_Equipment()
{
	m_pArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = m_pArrow;

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_pMesh->SetCollisionObjectType(UEngineTypes::ConvertToCollisionChannel(OTQ_Equipment));
	m_pMesh->SetCollisionResponseToChannel(UEngineTypes::ConvertToCollisionChannel(OTQ_Player), ECollisionResponse::ECR_Ignore);
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


