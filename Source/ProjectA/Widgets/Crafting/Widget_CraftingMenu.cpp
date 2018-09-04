// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_CraftingMenu.h"
#include "Widget_CraftingEntry.h"

#include <Components/VerticalBox.h>



void UWidget_CraftingMenu::InitWidget()
{
	m_pCraftingEntryList->ClearChildren();
}

FORCEINLINE void UWidget_CraftingMenu::AddCraftingEntryWidget(UWidget_CraftingEntry* _pEntry)
{
	m_pCraftingEntryList->AddChildToVerticalBox(_pEntry);
}


