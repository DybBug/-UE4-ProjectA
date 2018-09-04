// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Inventory.h"
#include "Widget_InventorySlot.h"
#include "../Widget_Main.h"
#include "Components/Component_Inventory.h"
#include "Operations/Operation_Widget.h"
#include "Operations/Operation_Slot.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>
#include <Engine.h>

#define LOCTEXT_NAMESPACE "Widget_Inventory"

void UWidget_Inventory::NativeConstruct()
{
	m_pCloseButton->OnClicked.AddDynamic(this, &UWidget_Inventory::_OnCloseButtonClicked);
}

void UWidget_Inventory::InitWidget(UWidget_Main* _pMain, UComponent_Inventory* _pInventory)
{
	UWidget_Base::InitWidget(_pMain);
	m_pInventory = _pInventory;

	m_pSlotPanel->ClearChildren();
}

bool UWidget_Inventory::GenerateSlots(FInventorySlot_Info* _pSlot, int _Row, int _Column)
{
	if (m_SlotWidgetClass)
	{	
		// #. 슬롯 위젯 생성 및 초기화.
		UWidget_InventorySlot* pInventorySlot = CreateWidget<UWidget_InventorySlot>(GetWorld(), m_SlotWidgetClass);
		pInventorySlot->InitWidget(m_pInventory, _pSlot, m_pMainWidget->GetDetailWidget());
		pInventorySlot->UpdateWidget();

		// #. 생성된 인벤토리 슬롯 추가 및 행/열 설정.
		UUniformGridSlot* pSlot = m_pSlotPanel->AddChildToUniformGrid(pInventorySlot);
		pSlot->SetRow(_Row);
		pSlot->SetColumn(_Column);

		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("\"InventorySlot Widget Class\" Find Failed."));
		return false;
	}
}

FReply UWidget_Inventory::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidget_Base::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}

	return FReply::Unhandled();
}

bool UWidget_Inventory::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UOperation_Slot* pSlotOper = Cast<UOperation_Slot>(InOperation))
	{
		return true;
	}
	return false;
}

void UWidget_Inventory::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	return UWidget_Base::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);	
}

void UWidget_Inventory::_OnCloseButtonClicked()
{
	if (m_pInventory)
	{
		m_pInventory->Close();
	}
}


#undef LOCTEXT_NAMESPACE
