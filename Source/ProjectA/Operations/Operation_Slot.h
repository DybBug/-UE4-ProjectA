// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Operation_Slot.generated.h"

/**
 * 
 */
class UWidget_InventorySlot;

UCLASS()
class PROJECTA_API UOperation_Slot : public UDragDropOperation
{
	GENERATED_BODY()
	
	UWidget_InventorySlot* m_pDraggedSlot;

public :
	void InitOperation(UWidget_InventorySlot* _pDraggedSlot);

	/* Get */
	FORCEINLINE UWidget_InventorySlot* const& GetDraggedSlot() const { return m_pDraggedSlot; }
};
