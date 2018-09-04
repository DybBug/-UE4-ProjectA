// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_EquipmentSlot.h"
#include "Widgets/Inventory/Widget_InventorySlot.h"
#include "Widgets/Misc/Widget_Detail.h"
#include "Components/Component_Equipment.h"
#include "Components/Component_Inventory.h"
#include "Items/Item_Equipment.h"
#include "Operations/Operation_Slot.h"

#include <Components/Border.h>
#include <Components/Image.h>


void UWidget_EquipmentSlot::NativePreConstruct()
{
	m_pOutline->SetBrushColor(m_DefaultColor);
	m_pBackground->SetBrushFromTexture(m_pBackgroundImage);
}

void UWidget_EquipmentSlot::InitWidget(UComponent_Equipment* _pEquipment, UWidget_Detail* _pDetailWidget)
{
	m_pEquipment = _pEquipment;
	m_pDetailWidget = _pDetailWidget;
}

void UWidget_EquipmentSlot::Show()
{
	if (m_pSlotInfo->pItem)
	{
		UTexture2D* pIcon = m_pSlotInfo->pItem->GetInfo().pIcon;
		m_pIcon->SetBrushFromTexture(pIcon);
		m_pIcon->SetRenderOpacity(1.0f);
	}
}

void UWidget_EquipmentSlot::Hide()
{
	SetToolTip(nullptr);
	m_pIcon->SetBrushFromTexture(nullptr);
	m_pIcon->SetRenderOpacity(0.f);
}

void UWidget_EquipmentSlot::BindEquipFunc(UComponent_Equipment* _pComp, Equip _pFunc)
{
	m_pEquipmentRef = _pComp;
	EquipFunc = _pFunc;
}

void UWidget_EquipmentSlot::BindUnEquipFunc(UComponent_Equipment* _pComp, UnEquip _pFunc)
{
	m_pUnEquipmentRef = _pComp;
	UnEquipFunc = _pFunc;
}


FReply UWidget_EquipmentSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (m_pSlotInfo->pItem)
	{		
		if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
		{
			(m_pUnEquipmentRef->*UnEquipFunc)();
			return FReply::Handled();
		}
	}
	return FReply::Handled();
}

void UWidget_EquipmentSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{

}

void UWidget_EquipmentSlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UOperation_Slot* pSlotOper = Cast<UOperation_Slot>(InOperation))
	{
		if (AItem_Equipment* pEquipment = Cast<AItem_Equipment>(pSlotOper->GetDraggedSlot()->GetSlotInfo()->pItem))
		{
			if (pEquipment->GetEquipmentType() == m_Type)
			{
				m_pOutline->SetBrushColor(m_OverlapColor);
				return;
			}
		}
		m_pOutline->SetBrushColor(m_FailColor);
		return;
	}
}

void UWidget_EquipmentSlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	m_pOutline->SetBrushColor(m_DefaultColor);
}

bool UWidget_EquipmentSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UOperation_Slot* pSlotOper = Cast<UOperation_Slot>(InOperation))
	{
		if (AItem_Equipment* pEquipment = Cast<AItem_Equipment>(pSlotOper->GetDraggedSlot()->GetSlotInfo()->pItem))
		{
			if (pEquipment->GetEquipmentType() == m_Type)
			{
				pSlotOper->GetDraggedSlot()->GetSlotInfo()->pItem = nullptr;
				pSlotOper->GetDraggedSlot()->GetSlotInfo()->Amount = 0;
				pSlotOper->GetDraggedSlot()->GetSlotInfo()->pSlotWidget->UpdateWidget();
				(m_pEquipmentRef->*EquipFunc)(pEquipment);
				return true;
			}
		}
	}
	return true;
}

void UWidget_EquipmentSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	m_pOutline->SetBrushColor(m_DefaultColor);
}

void UWidget_EquipmentSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	m_pOutline->SetBrushColor(m_OverlapColor);

	if (m_pSlotInfo->pItem && m_pDetailWidget)
	{
		m_pDetailWidget->UpdateWidget(m_pSlotInfo->pItem->GetClass());
		SetToolTip(m_pDetailWidget);
	}
}

void UWidget_EquipmentSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{

	m_pOutline->SetBrushColor(m_DefaultColor);

	if (m_pSlotInfo->pItem && m_pDetailWidget)
	{
		SetToolTip(nullptr);
	}
}

