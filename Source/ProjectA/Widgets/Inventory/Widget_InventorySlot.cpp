// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_InventorySlot.h"
#include "Components/Component_Inventory.h"
#include "Operations/Operation_Slot.h"
#include "Items/Item_Base.h"
#include "Widgets/Misc/Widget_Detail.h"
#include "Players/Player_Character.h"

#include <Components/Border.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

void UWidget_InventorySlot::NativePreConstruct()
{
	m_pOutline->SetBrushColor(m_DefaultColor);
}

bool UWidget_InventorySlot::InitWidget(UComponent_Inventory* _pInventory, FInventorySlot_Info* _pInfoRef, UWidget_Detail* _pDetailWidget)
{
	m_pInventory = _pInventory;
	m_pSlotInfo = _pInfoRef;
	m_pDetailWidget = _pDetailWidget;

	m_pSlotInfo->pSlotWidget = this;

	return true;
}

void UWidget_InventorySlot::UpdateWidget()
{
	if (m_pSlotInfo)
	{
		if (m_pSlotInfo->pItem)
		{
			m_pIcon->SetBrushFromTexture(m_pSlotInfo->pItem->GetInfo().pIcon);

			if (m_pSlotInfo->pItem->GetInfo().bCanStacked && (m_pSlotInfo->Amount > 0))
			{
				m_pAmountText->SetText(FText::AsNumber(m_pSlotInfo->Amount));
				m_pAmountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
			{
				m_pAmountText->SetText(FText::AsNumber(0));
				m_pAmountText->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		else
		{
			SetToolTip(nullptr);
			m_pIcon->SetBrushFromTexture(nullptr);
			m_pAmountText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UWidget_InventorySlot::Show()
{
	m_pIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_pAmountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWidget_InventorySlot::Hide()
{
	m_pIcon->SetVisibility(ESlateVisibility::Hidden);
	m_pAmountText->SetVisibility(ESlateVisibility::Hidden);
}

FReply UWidget_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (m_pSlotInfo->pItem)
	{
		// #. 마우스 왼쪽 클릭.
		if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			FReply Result(FReply::Handled());

			Result.DetectDrag(this->TakeWidget(), EKeys::LeftMouseButton);
			return Result;
		}
		
		// #. 마우스 오른쪽 클릭.
		if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
		{
			if (m_pSlotInfo->pItem->GetInfo().bCanUsed)
			{
				if(m_pSlotInfo->pItem->OnUse(m_pSlotInfo))
				{
					UpdateWidget();
				}
			}

			return FReply::Handled();
		}
	}	

	return FReply::Handled();
}

void UWidget_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{

	// #. 위젯 DragDropOperation 생성.
	UOperation_Slot* pOper_Slot = NewObject<UOperation_Slot>(UOperation_Slot::StaticClass());
	pOper_Slot->InitOperation(this);
	pOper_Slot->DefaultDragVisual = this;
	pOper_Slot->Pivot = EDragPivot::MouseDown;

	OutOperation = pOper_Slot;
}

bool UWidget_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UOperation_Slot* pOper_Slot = Cast<UOperation_Slot>(InOperation))
	{
		UWidget_InventorySlot* pFromSlot = Cast<UWidget_InventorySlot>(pOper_Slot->GetDraggedSlot());
		FInventorySlot_Info* pFromSlotInfo = pFromSlot->GetSlotInfo();
		if (!m_pSlotInfo->pItem)
		{
			m_pInventory->MoveItem(m_pSlotInfo->SlotIndex, pFromSlotInfo->SlotIndex);
		}
		else
		{
			if ((pFromSlot != this) && (m_pSlotInfo->pItem->GetClass() == pFromSlotInfo->pItem->GetClass()))
			{
				m_pInventory->CombineItem(m_pSlotInfo->SlotIndex, pFromSlotInfo->SlotIndex);
			}
			else
			{
				m_pInventory->SwapItem(m_pSlotInfo->SlotIndex, pFromSlotInfo->SlotIndex);
			}
		}	
		return true;
	}
	return false;
}

void UWidget_InventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	m_pOutline->SetBrushColor(m_OverlapColor);

	if (m_pSlotInfo->pItem && m_pDetailWidget)
	{
		m_pDetailWidget->UpdateWidget(m_pSlotInfo->pItem->GetClass());
		SetToolTip(m_pDetailWidget);
	}
}

void UWidget_InventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	m_pOutline->SetBrushColor(m_DefaultColor);

	if (m_pSlotInfo->pItem && m_pDetailWidget)
	{
		SetToolTip(nullptr);
	}
}

void UWidget_InventorySlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	if (UOperation_Slot* pOper_Slot = Cast<UOperation_Slot>(InOperation))
	{
		m_pOutline->SetBrushColor(m_OverlapColor);
	}
}

void UWidget_InventorySlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	if (UOperation_Slot* pOper_Slot = Cast<UOperation_Slot>(InOperation))
	{
		m_pOutline->SetBrushColor(m_DefaultColor);
	}
}
