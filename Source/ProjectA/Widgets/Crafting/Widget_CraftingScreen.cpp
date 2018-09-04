// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_CraftingScreen.h"
#include "Widget_Recipe.h"
#include "Components/Component_Crafting.h"
#include "Components/Component_Inventory.h"
#include "Items/Item_Base.h"

#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>
#include <Components/VerticalBox.h>
#include <Components/Button.h>
#include <WidgetTree.h>


#define LOCTEXT_NAMESPACE "Format"

void UWidget_CraftingScreen::NativePreConstruct()
{
	for (int i = 0; i < (int)EStat_Types::Max; ++i)
	{
		UTextBlock* pTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		pTextBlock->SetVisibility(ESlateVisibility::Collapsed);
		UUniformGridSlot* pSlot = m_pAbilityList->AddChildToUniformGrid(pTextBlock);
		int Row = i / 2;
		int Column = i % 2;
		pSlot->SetRow(Row);
		pSlot->SetColumn(Column);
	}
}

void UWidget_CraftingScreen::NativeConstruct()
{
	m_pMakingButton->OnClicked.AddDynamic(this, &UWidget_CraftingScreen::_OnMakingButtonClicked);
	m_pCancelButton->OnClicked.AddDynamic(this, &UWidget_CraftingScreen::_OnCancelButtonClicked);
}

void UWidget_CraftingScreen::InitWidget(UComponent_Crafting* _pComp)
{
	m_bIsShow = false;
	m_pMakingButton->SetIsEnabled(false);

	m_pCrafting = _pComp;
}

void UWidget_CraftingScreen::UpdateWidget()
{
	if (m_RecipeWidgetClass)
	{
		bool bIsAmountEnough = true;

		for (int i = 0; i < m_CraftingInfo.RecipeList.Num(); ++i)
		{
			UWidget_Recipe* pRecipeWidget = Cast<UWidget_Recipe>(m_pRecipeList->GetChildAt(i));
			pRecipeWidget->UpdateWidget();

			bIsAmountEnough = (bIsAmountEnough && pRecipeWidget->IsAmountEnough());
		}

		if (bIsAmountEnough)
		{
			m_pMakingButton->SetIsEnabled(true);
		}
		else
		{
			m_pMakingButton->SetIsEnabled(false);
		}
	}
}

void UWidget_CraftingScreen::Show(const FCrafting_Info& _CraftingInfo)
{
	m_CraftingInfo = _CraftingInfo;
	m_bIsShow = true;

	_SetupAbilityList();
	_SetupRecipeList();

	const FItem_Info& ItemInfo = m_CraftingInfo.CraftItemClass.GetDefaultObject()->GetInfo();
	m_pIcon->SetBrushFromTexture(ItemInfo.pIcon);
	m_pNameText->SetText(FText::FromName(ItemInfo.Name));

	FString DescStr = ItemInfo.Description.ToString().Replace(L"/n", L"\n");
	m_pDescriptionText->SetText(FText::FromString(DescStr));	
	
	SetVisibility(ESlateVisibility::Visible);
}

void UWidget_CraftingScreen::Hide()
{
	m_pRecipeList->ClearChildren();
	m_bIsShow= false;

	SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_CraftingScreen::_SetupAbilityList()
{
	int Index = 0;
	
	for (auto Ability : m_CraftingInfo.CraftItemClass.GetDefaultObject()->GetInfo().AbilityList)
	{
		UTextBlock* pTextBlock = Cast<UTextBlock>(m_pAbilityList->GetChildAt(Index));
		FString  StatStr = CONVERT_DISPLAYNAME_TO_STRING(L"EStat_Types", Ability.Key);
		FText Format = FText::Format(LOCTEXT("Format", "{0} : {1}"), FText::FromString(StatStr), Ability.Value);
		pTextBlock->SetText(Format);
		pTextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Index++;
	}
}

void UWidget_CraftingScreen::_SetupRecipeList()
{
	if (m_RecipeWidgetClass)
	{
		for (auto Recipe : m_CraftingInfo.RecipeList)
		{
			UWidget_Recipe* pRecipeWidget = CreateWidget<UWidget_Recipe>(GetWorld(), m_RecipeWidgetClass);
			pRecipeWidget->InitWidget(Recipe.Key.GetDefaultObject(), Recipe.Value);
			pRecipeWidget->UpdateWidget();
			m_pRecipeList->AddChildToVerticalBox(pRecipeWidget);
		}
	}
}

void UWidget_CraftingScreen::_OnMakingButtonClicked()
{
	 m_pCrafting->CreateItem(m_CraftingInfo);
}

void UWidget_CraftingScreen::_OnCancelButtonClicked()
{
	Hide();
}

#undef LOCTEXT_NAMESPACE
