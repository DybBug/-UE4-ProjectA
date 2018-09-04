// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Pickup.h"
#include "Widget_PickupSlot.h"
#include "../Widget_Main.h"
#include "Items/Item_Base.h"
#include "Actors/Chest.h"
#include "Components/Component_Pickup.h"

#include <Components/Button.h>
#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>



void UWidget_Pickup::NativeConstruct()
{
	Super::NativeConstruct();

	m_pCloseButton->OnClicked.AddDynamic(this, &UWidget_Pickup::_OnCloseButtonClicked);
}

void UWidget_Pickup::InitWidget(UWidget_Main* _pMain)
{
	UWidget_Base::InitWidget(_pMain);
}

void UWidget_Pickup::Show(UComponent_Pickup* _pPickup)
{
	m_pSlotPanel->ClearChildren();
	m_pPickup = _pPickup;

	if (m_SlotWidgetClass)
	{
		for (int i = 0; i < m_pPickup->ItemCount(); ++i)
		{
			if (m_pPickup->GetItemInfoAtIndex(i)->ItemClass && (m_pPickup->GetItemInfoAtIndex(i)->Amount > 0))
			{
				UWidget_PickupSlot* pPickupSlot = CreateWidget<UWidget_PickupSlot>(this, m_SlotWidgetClass);
				pPickupSlot->InitWidget(m_pPickup, i, m_pMainWidget->GetDetailWidget());
				m_pSlotPanel->AddChildToVerticalBox(pPickupSlot);
				m_pSlotPanel->AddChildToVerticalBox(pPickupSlot);
			}
		}
	}
	
	SetVisibility(ESlateVisibility::Visible);
}

void UWidget_Pickup::Hide()
{
	m_pSlotPanel->ClearChildren();
	SetVisibility(ESlateVisibility::Hidden);
}

FReply UWidget_Pickup::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidget_Base::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}
	return FReply::Unhandled();
}

void UWidget_Pickup::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	return UWidget_Base::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UWidget_Pickup::_OnCloseButtonClicked()
{
	Cast<IInterface_Interaction>(m_pPickup->GetOwner())->UnInteract();
}
