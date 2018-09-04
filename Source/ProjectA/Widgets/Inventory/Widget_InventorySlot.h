// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_InventorySlot.generated.h"

/**
 * 
 */
class UBorder;
class UImage;
class UTextBlock;
class AItem_Base;
class UComponent_Inventory;
class UWidget_Detail;

struct FInventorySlot_Info;


UCLASS()
class PROJECTA_API UWidget_InventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	virtual void NativePreConstruct() override;
	
protected :
	UPROPERTY(BlueprintReadOnly)
	UBorder* m_pOutline;

	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UTextBlock* m_pAmountText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	FLinearColor m_DefaultColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	FLinearColor m_OverlapColor;

	UComponent_Inventory* m_pInventory;

	UWidget_Detail* m_pDetailWidget = nullptr;

	FInventorySlot_Info* m_pSlotInfo = nullptr;

public :
	bool InitWidget(UComponent_Inventory* _pInventory, FInventorySlot_Info* _pInfoRef, UWidget_Detail* _pDetailWidget);
	void UpdateWidget();

	void Show();
	void Hide();

	/* Get */
	FORCEINLINE FInventorySlot_Info* const& GetSlotInfo() const { return m_pSlotInfo; }


protected :
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
