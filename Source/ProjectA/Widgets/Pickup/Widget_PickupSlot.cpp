// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_PickupSlot.h"
#include "Widgets/Misc/Widget_Detail.h"
#include "Items/Item_Base.h"
#include "Components/Component_Pickup.h"
#include "Components/Component_Inventory.h"
#include "Players/Player_Character.h"

#include <Components/Border.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

#define LOCTEXT_NAMESPACE "Format"

void UWidget_PickupSlot::NativePreConstruct()
{
	m_pBackground->SetBrushColor(m_DefaultColor);
}

void UWidget_PickupSlot::InitWidget(UComponent_Pickup* _pPickup, int _Index, UWidget_Detail* _pDetail)
{
	m_pPickup = _pPickup;
	m_Index = _Index;
	m_pDetailWidget = _pDetail;

	const FPickupSlot_Info* pInfo = m_pPickup->GetItemInfoAtIndex(m_Index);

	m_pIcon->SetBrushFromTexture(pInfo->ItemClass.GetDefaultObject()->GetInfo().pIcon);
	m_pNameText->SetText(FText::FromName(pInfo->ItemClass.GetDefaultObject()->GetInfo().Name));
	m_pAmountText->SetText(FText::AsNumber(pInfo->Amount));
}


FReply UWidget_PickupSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		APlayer_Character* pPlayer = Cast<APlayer_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (pPlayer)
		{
			const FPickupSlot_Info* pInfo = m_pPickup->GetItemInfoAtIndex(m_Index);
		
			FActorSpawnParameters Param;
			Param.Owner = pPlayer;			
			AItem_Base* pItem = GetWorld()->SpawnActor<AItem_Base>(pInfo->ItemClass, Param);
		
			int Rest = pPlayer->GetInventory()->AddItem(pItem, pInfo->Amount);

			m_pPickup->RemoveItemAtIndex(m_Index, (pInfo->Amount - Rest));

			if (Rest)
			{					
				m_pAmountText->SetText(FText::AsNumber(pInfo->Amount));
			}
			else
			{
				SetVisibility(ESlateVisibility::Collapsed);
			}

			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}

void UWidget_PickupSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	m_pBackground->SetBrushColor(m_OverlapColor);

	if (m_pPickup->GetItemInfoAtIndex(m_Index)->ItemClass && m_pDetailWidget)
	{
		m_pDetailWidget->UpdateWidget(m_pPickup->GetItemInfoAtIndex(m_Index)->ItemClass);
		SetToolTip(m_pDetailWidget);
	}
}


void UWidget_PickupSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	m_pBackground->SetBrushColor(m_DefaultColor);

	if (m_pPickup->GetItemInfoAtIndex(m_Index)->ItemClass && m_pDetailWidget)
	{
		SetToolTip(nullptr);
	}
}

#undef LOCTEXT_NAMESPACE
