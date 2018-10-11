// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_Base.h"
#include "Widget_Pickup.generated.h"

/**
 * 
 */
class UButton;
class UVerticalBox;
class UComponent_Pickup;
class UWidget_PickupSlot;
class UWidget_Main;


UCLASS()
class PROJECTA_API UWidget_Pickup : public UWidget_Base
{
	GENERATED_BODY()

protected :
	virtual void NativeConstruct() override;
	
protected :
	UPROPERTY()
	UButton* m_pCloseButton;

	UPROPERTY()
	UVerticalBox* m_pSlotPanel;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_PickupSlot> m_SlotWidgetClass;
	
public :
	virtual void InitWidget(UWidget_Main* _pMain, UComponent_Base* _pComponent) override;

	void GenerateSlots();
	void RemoveSlots();

protected :
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

protected :
	UFUNCTION()
	void _OnCloseButtonClicked();
};
