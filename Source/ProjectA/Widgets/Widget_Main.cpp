// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Main.h"
#include "Inventory/Widget_Inventory.h"
#include "Inventory/Widget_InventorySlot.h"
#include "Equipment/Widget_Equipment.h"
#include "Stat/Widget_Stat.h"
#include "Crafting/Widget_Crafting.h"
#include "SkillTree/Widget_SkillTree.h"
#include "Hotkey/Widget_Hotkey.h"
#include "Pickup/Widget_Pickup.h"
#include "Misc/Widget_Detail.h"
#include "Misc/Widget_ThrowAway.h"
#include "Misc/Widget_StatBar.h"
#include "Misc/Widget_Compass.h"
#include "Players/Player_Character.h"
#include "Components/Component_Inventory.h"
#include "Operations/Operation_Widget.h"
#include "Operations/Operation_Slot.h"



bool UWidget_Main::InitWidget(APlayer_Character* _pPlayer)
{
	m_pPlayer = _pPlayer;

	if (m_DetailWidgetClass)
	{
		m_pDetailWidget = CreateWidget<UWidget_Detail>(GetWorld(), m_DetailWidgetClass);
		m_pDetailWidget->InitWidget(this);
	}

	m_pInventoryWidget->InitWidget(this, m_pPlayer->GetInventory());
	m_pEquipmentWidget->InitWidget(this, m_pPlayer->GetEquipment());
	m_pStatWidget->InitWidget(this, m_pPlayer->GetStat());
	m_pThrowAwayWidget->InitWidget(this, m_pPlayer->GetInventory());
	m_pCraftingWidget->InitWidget(this, m_pPlayer->GetCrafting());
	m_pSkillTreeWidget->InitWidget(this, m_pPlayer->GetSkillTree());
	m_pPickupWidget->InitWidget(this, nullptr);
	m_pHealthBarWidget->InitWidget(this);
	m_pManaBarWidget->InitWidget(this);
	m_pStaminaBarWidget->InitWidget(this);
	m_pCompassWidget->InitWidget(this, nullptr);

	return true;
}

bool UWidget_Main::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (UOperation_Slot* pOperSlot = Cast<UOperation_Slot>(InOperation))
	{
		UWidget_InventorySlot* pSlot = Cast<UWidget_InventorySlot>(pOperSlot->GetDraggedSlot());

		m_pThrowAwayWidget->Show(pSlot->GetSlotInfo());
		return true;
	}

	return false;
}
