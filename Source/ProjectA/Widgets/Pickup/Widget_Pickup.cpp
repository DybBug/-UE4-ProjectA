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

void UWidget_Pickup::InitWidget(UWidget_Main* _pMain, UComponent_Base* _pComponent)
{
	UWidget_Base::InitWidget(_pMain, _pComponent);
}

void UWidget_Pickup::GenerateSlots()
{
	m_pSlotPanel->ClearChildren();
	UComponent_Pickup* pComp = Cast<UComponent_Pickup>(m_pComponent);

	if (m_SlotWidgetClass)
	{
		for (int i = 0; i < pComp->ItemCount(); ++i)
		{
			if (pComp->GetItemInfoAtIndex(i)->ItemClass && (pComp->GetItemInfoAtIndex(i)->Amount > 0))
			{
				UWidget_PickupSlot* pPickupSlot = CreateWidget<UWidget_PickupSlot>(this, m_SlotWidgetClass);
				pPickupSlot->InitWidget(pComp, i, m_pMainWidget->GetDetailWidget());
				m_pSlotPanel->AddChildToVerticalBox(pPickupSlot);
				m_pSlotPanel->AddChildToVerticalBox(pPickupSlot);
			}
		}
	}
}

void UWidget_Pickup::RemoveSlots()
{
	m_pSlotPanel->ClearChildren();
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
	UComponent_Pickup* pComp = Cast<UComponent_Pickup>(m_pComponent);
	Cast<IInterface_Interaction>(pComp->GetOwner())->UnInteract();
}
