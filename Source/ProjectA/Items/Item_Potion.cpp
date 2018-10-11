// Fill out your copyright notice in the Description page of Project Settings.

#include "Item_Potion.h"
#include "Players/Player_Character.h"
#include "Components/Component_Inventory.h"
#include "Widgets/Inventory/Widget_InventorySlot.h"

void AItem_Potion::InitItem(AActor* _pOwner)
{
	AItem_Base::InitItem(_pOwner);
}

bool AItem_Potion::OnUse(FInventorySlot_Info* const pSlotInfo)
{
	bool bSuccess = false;
	if (m_pPlayer)
	{
		for (auto ItemAbility : m_Info.AbilityList)
		{
			if (ItemAbility.Key == EStat_Types::Experience)
			{
				bSuccess = m_pPlayer->GainExperience(ItemAbility.Value);
			}
			else
			{
				bSuccess = m_pPlayer->ModifyCurrentStat(ItemAbility.Key, ItemAbility.Value);
			}

			if (bSuccess)
			{
				pSlotInfo->Amount--;
				if (pSlotInfo->Amount == 0)
				{
					pSlotInfo->pItem = nullptr;
					Destroy();
				}
				//pSlotInfo->pSlotWidget->UpdateWidget();
				return bSuccess;
			}
		}

	}
	return bSuccess;
}


