// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_CraftingEntry.h"
#include "Components/Component_Crafting.h"
#include "Widget_CraftingScreen.h"
#include "Items/Item_Base.h"

#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>


void UWidget_CraftingEntry::NativeConstruct()
{
	m_pEntryButton->OnClicked.AddDynamic(this, &UWidget_CraftingEntry::_OnEntryButtonClicked);
}

void UWidget_CraftingEntry::InitWidget(int _Index, UWidget_CraftingScreen* _pWidget)
{
	m_CraftingItemIndex = _Index;
	m_pCraftingScreenWidget = _pWidget;

	const FCrafting_Info& CraftingInfo = m_pCraftingScreenWidget->GetCrafting()->GetCraftingItemAt(_Index);
	const FItem_Info& ItemInfo = CraftingInfo.CraftItemClass.GetDefaultObject()->GetInfo();

	m_pIcon->SetBrushFromTexture(ItemInfo.pIcon);
	m_pNameText->SetText(FText::FromName(ItemInfo.Name));

	FString Description = ItemInfo.Description.ToString().Replace(L"/n", L"\n");
	m_pDescriptionText->SetText(FText::FromString(Description));
}

void UWidget_CraftingEntry::_OnEntryButtonClicked()
{
	m_pCraftingScreenWidget->Show(m_CraftingItemIndex);
	m_pCraftingScreenWidget->UpdateWidget();
}
