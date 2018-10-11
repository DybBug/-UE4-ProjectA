// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_Base.h"
#include "Widget_Inventory.generated.h"

/**
 * 
 */
class UButton;
class UUniformGridPanel;
class UTextBlock;
class UComponent_Inventory;
class UWidget_Main;
class UWidget_InventorySlot;

struct FInventorySlot_Info;


UCLASS()
class PROJECTA_API UWidget_Inventory : public UWidget_Base
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
protected :
	UPROPERTY()
	UButton* m_pCloseButton;

	UPROPERTY()
	UUniformGridPanel* m_pSlotPanel;

	UPROPERTY()
	UTextBlock* m_pSlotCountText;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_InventorySlot> m_SlotWidgetClass;

public :
	virtual void InitWidget(UWidget_Main* _pMain, UComponent_Base* _pComponent) override;

	bool GenerateSlots(FInventorySlot_Info* _pSlot, int _Row, int _Column);

protected :
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;


private :	
	UFUNCTION()
	void _OnCloseButtonClicked();
};
