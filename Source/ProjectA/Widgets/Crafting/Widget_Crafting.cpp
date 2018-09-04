// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Crafting.h"
#include "Widget_CraftingEntry.h"
#include "Widget_CraftingMenu.h"
#include "Widget_CraftingScreen.h"
#include "Widgets/Widget_Main.h"
#include "Items/Item_Base.h"
#include "Components/Component_Crafting.h"

#include <Components/Button.h>
#include <Components/CanvasPanel.h>
#include <Components/WidgetSwitcher.h>


void UWidget_Crafting::NativeConstruct()
{
	m_pCloseButton->OnClicked.AddDynamic(this, &UWidget_Crafting::_OnCloseButtonClicked);
	m_pConsumablesButton->OnClicked.AddDynamic(this, &UWidget_Crafting::_OnConsumablesButtonClicked);
	m_pEquipmentButton->OnClicked.AddDynamic(this, &UWidget_Crafting::_OnEquipmentButtonClicked);
}

void UWidget_Crafting::InitWidget(UWidget_Main* _pMain, UComponent_Crafting* _pComponent)
{
	UWidget_Base::InitWidget(_pMain);
	m_pCrafting = _pComponent;
	m_pCraftingScreen->InitWidget(m_pCrafting);
}

void UWidget_Crafting::GenerateEntries()
{
	m_pConsumablesMenu->InitWidget();
	m_pEquipmentMenu->InitWidget();

	if (m_EntryWidgetClass)
	{
		for (auto CraftingItem : m_pCrafting->GetCraftingItems())
		{
			UWidget_CraftingEntry* pEntryWidget = CreateWidget<UWidget_CraftingEntry>(this, m_EntryWidgetClass);
			pEntryWidget->InitWidget(CraftingItem, m_pCraftingScreen);

			if (CraftingItem.CraftItemClass.GetDefaultObject()->GetInfo().Type == EItem_Types::Consumables)
			{
				m_pConsumablesMenu->AddCraftingEntryWidget(pEntryWidget);
			}
			else if (CraftingItem.CraftItemClass.GetDefaultObject()->GetInfo().Type == EItem_Types::Equipment)
			{
				m_pEquipmentMenu->AddCraftingEntryWidget(pEntryWidget);
			}
		}
	}
}

void UWidget_Crafting::UpdateWidget()
{
	if (m_pCraftingScreen->GetIsShow())
	{
		m_pCraftingScreen->UpdateWidget();
	}
}

void UWidget_Crafting::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UWidget_Crafting::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
	m_pCraftingScreen->Hide();
}

void UWidget_Crafting::_OnCloseButtonClicked()
{
	if (m_pCrafting)
	{
		m_pCrafting->SetIsOpen(false);
		Hide();
	}
}

void UWidget_Crafting::_OnConsumablesButtonClicked()
{
	m_pCraftingMenuList->SetActiveWidgetIndex(0);
}

void UWidget_Crafting::_OnEquipmentButtonClicked()
{
	m_pCraftingMenuList->SetActiveWidgetIndex(1);
}


