// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Recipe.h"
#include "Components/Component_Crafting.h"
#include "Components/Component_Inventory.h"
#include "Items/Item_Base.h"
#include "Players/Player_Character.h"


#include <Components/Image.h>
#include <Components/TextBlock.h>

#define LOCTEXT_NAMESPACE "Format"

void UWidget_Recipe::InitWidget(const AItem_Base* const& _pRecipeItem, int _Amount)
{
	m_pRecipeItem = _pRecipeItem;
	m_MaxAmount = _Amount;
	m_CurrentAmount = 0;
}

void UWidget_Recipe::UpdateWidget()
{
	const FItem_Info& ItemInfo = m_pRecipeItem->GetInfo();

	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwningPlayerPawn());
	m_CurrentAmount = pPlayer->GetInventory()->GetAmountItem(m_pRecipeItem->GetClass());

	FText Format = FText::Format(LOCTEXT("Format", "x{0}/{1}"), m_CurrentAmount, m_MaxAmount);
	m_pAmountText->SetText(Format);

	FLinearColor TextColor = (m_CurrentAmount < m_MaxAmount) ? FLinearColor::Red : FLinearColor::Green;
	m_pAmountText->SetColorAndOpacity(TextColor);

	m_pIcon->SetBrushFromTexture(ItemInfo.pIcon);
}

bool UWidget_Recipe::IsAmountEnough()
{
	return m_CurrentAmount >= m_MaxAmount;
}

#undef LOCTEXT_NAMESPACE

