// Fill out your copyright notice in the Description page of Project Settings.

#include "Operation_Slot.h"
#include "Widgets/Inventory/Widget_InventorySlot.h"




void UOperation_Slot::InitOperation(UUserWidget* _pDraggedSlot)
{
	m_pDraggedSlot = _pDraggedSlot;
}
