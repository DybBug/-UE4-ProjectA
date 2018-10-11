// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_Base.h"
#include "Widget_ThrowAway.generated.h"

/**
 * 
 */

class UImage;
class UTextBlock;
class UButton;
class UHorizontalBox;
class UWidget_Main;
class UComponent_Inventory;

struct FInventorySlot_Info;


UCLASS()
class PROJECTA_API UWidget_ThrowAway : public UWidget_Base
{
	GENERATED_BODY()

protected :
	virtual void NativeConstruct() override;
	
protected :
	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UTextBlock* m_pNameText;

	UPROPERTY()
	UTextBlock* m_pAmountText;

	UPROPERTY()
	UButton* m_pMinusButton;

	UPROPERTY()
	UButton* m_pPlusButton;

	UPROPERTY()
	UButton* m_pConfirmButton;

	UPROPERTY()
	UButton* m_pCancelButton;

	UPROPERTY()
	UHorizontalBox* m_pAmountBox;

	//..
	UPROPERTY()
	FTimerHandle m_hMinusTimer;

	UPROPERTY()
	FTimerHandle m_hPlusTimer;

	FInventorySlot_Info* m_pSlotInfo;

	int m_CurrentThrowAmount;
	int m_MaxThrowAmount;	

	int m_ClickCount;

public :
	virtual void InitWidget(UWidget_Main* _pMainWidget, UComponent_Base* _pComponent) override;

	void Show(FInventorySlot_Info* _pSlotInfo);
	void Hide();

protected :
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

private :
	UFUNCTION()
	void _IncreaseAmount();

	UFUNCTION()
	void _DecreaseAmount();

	UFUNCTION()
	void _ResetClickCount();

	/* Button */
	UFUNCTION()
	void _OnMinusButtonClicked();

	UFUNCTION()
	void _OnMinusButtonPressed();

	UFUNCTION()
	void _OnMinusButtonReleased();

	UFUNCTION()
	void _OnPlusButtonClicked();

	UFUNCTION()
	void _OnPlusButtonPressed();

	UFUNCTION()
	void _OnPlusButtonReleased();

	UFUNCTION()
	void _OnConfirmButtonClicked();

	UFUNCTION()
	void _OnCancelButtonClicked();
	
};
