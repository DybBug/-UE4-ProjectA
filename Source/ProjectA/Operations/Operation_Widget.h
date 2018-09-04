// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Operation_Widget.generated.h"

/**
 * 
 */
class UUserWidget;
class UWidget_Main;

UCLASS()
class PROJECTA_API UOperation_Widget : public UDragDropOperation
{
	GENERATED_BODY()
	
protected :
	UUserWidget* m_pDraggedWidget;
	FVector2D m_Offset;

	UWidget_Main* m_pMainWidget;

public :
	void InitOperation(UWidget_Main* _pMainWidget, UUserWidget* _pDraggedWidget, const FVector2D& _Offset);

	void Drop_Implementation(const FPointerEvent& PointerEvent);
	void DragCancelled_Implementation(const FPointerEvent& PointerEvent);
	void Dragged_Implementation(const FPointerEvent& PointerEvent);

	/* Get */
	FORCEINLINE UUserWidget* const& GetDraggedWidget() const { return m_pDraggedWidget; }

	FORCEINLINE const FVector2D& GetOffset() const { return m_Offset; }
	
};
