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

void UWidget_Crafting::InitWidget(UWidget_Main* _pMain, UComponent_Base* _pComponent)
{
	UWidget_Base::InitWidget(_pMain, _pComponent);

	UComponent_Crafting* pComp = Cast<UComponent_Crafting>(m_pComponent);
	m_pCraftingScreen->InitWidget(pComp);
}

void UWidget_Crafting::GenerateEntries()
{
	m_pConsumablesMenu->InitWidget();
	m_pEquipmentMenu->InitWidget();

	if (m_EntryWidgetClass)
	{
		UComponent_Crafting* pComp = Cast<UComponent_Crafting>(m_pComponent);
		for (int i = 0; i < pComp->GetCraftingItems().Num(); ++i)
		{
			UWidget_CraftingEntry* pEntryWidget = CreateWidget<UWidget_CraftingEntry>(this, m_EntryWidgetClass);
			pEntryWidget->InitWidget(i, m_pCraftingScreen);

			if (pComp->GetCraftingItems()[i].CraftItemClass.GetDefaultObject()->GetInfo().Type == EItem_Types::Consumables)
			{
				m_pConsumablesMenu->AddCraftingEntryWidget(pEntryWidget);
			}
			else if (pComp->GetCraftingItems()[i].CraftItemClass.GetDefaultObject()->GetInfo().Type == EItem_Types::Equipment)
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


void UWidget_Crafting::_OnCloseButtonClicked()
{
	m_pComponent->Close();
}

void UWidget_Crafting::_OnConsumablesButtonClicked()
{
	m_pCraftingMenuList->SetActiveWidgetIndex(0);
}

void UWidget_Crafting::_OnEquipmentButtonClicked()
{
	m_pCraftingMenuList->SetActiveWidgetIndex(1);
}


