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
#include "Misc/Widget_BuffIcon.h"
#include "Players/Player_Character.h"
#include "Skills/Skill_Buff.h"
#include "Components/Component_Inventory.h"
#include "Operations/Operation_Widget.h"
#include "Operations/Operation_Slot.h"

#include <Components/HorizontalBox.h>



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

void UWidget_Main::AddBuff(ASkill_Buff* _pBuff)
{
	if (m_BuffIconWidgetClass)
	{
		UWidget_BuffIcon* pWidget = Cast<UWidget_BuffIcon>(CreateWidget<UWidget_BuffIcon>(this, m_BuffIconWidgetClass));
		m_pBuffList->AddChildToHorizontalBox(pWidget);

		_pBuff->SetBuffIconWidget(pWidget);
		pWidget->InitWidget(_pBuff->GetInfo().pIcon);
	}	
}

void UWidget_Main::ResetBuffAt(int i)
{
	UWidget_BuffIcon* pWidget = Cast<UWidget_BuffIcon>(m_pBuffList->GetChildAt(i));
	pWidget->UpdateWidget(0.f);
}

void UWidget_Main::RemoveBuffAt(int i)
{
	m_pBuffList->GetChildAt(i)->RemoveFromParent();
}

void UWidget_Main::UpdateStatBar(EStat_Types _Type, float _CurrentValue, float _MaxValue)
{
	UWidget_StatBar* pStatBar = nullptr;
	switch (_Type)
	{
	case EStat_Types::Health:
	{
		m_pHealthBarWidget->UpdateWidget(_CurrentValue, _MaxValue);
		break;
	}
	case EStat_Types::Mana:
	{
		m_pManaBarWidget->UpdateWidget(_CurrentValue, _MaxValue);
		break;
	}
	case EStat_Types::Stamina:
	{
		m_pStaminaBarWidget->UpdateWidget(_CurrentValue, _MaxValue);
		break;
	}
	default: break;
	}
}

bool UWidget_Main::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (UOperation_Slot* pOperSlot = Cast<UOperation_Slot>(InOperation))
	{
		UWidget_InventorySlot* pSlot = Cast<UWidget_InventorySlot>(pOperSlot->GetDraggedSlot());
		if (pSlot)
		{
			m_pThrowAwayWidget->Show(pSlot->GetSlotInfo());
			return true;
		}
		return false;
	}

	return false;
}
