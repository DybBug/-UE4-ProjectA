// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Operation_Slot.generated.h"

/**
 * 
 */

UCLASS()
class PROJECTA_API UOperation_Slot : public UDragDropOperation
{
	GENERATED_BODY()
	
	UUserWidget* m_pDraggedSlot;

public :
	void InitOperation(UUserWidget* _pDraggedSlot);

	/* Get */
	FORCEINLINE UUserWidget* const& GetDraggedSlot() const { return m_pDraggedSlot; }
};
