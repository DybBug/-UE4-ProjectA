// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HotkeySlot.generated.h"

/**
 * 
 */
class UTextBlock;
class UBorder;
class UImage;

UCLASS()
class PROJECTA_API UWidget_HotkeySlot : public UUserWidget
{
	GENERATED_BODY()
	
public :
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected :
	UPROPERTY()
	UTextBlock* m_pHotkeyText;

	UPROPERTY()
	UBorder* m_pOutline;

	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UTextBlock* m_pNum;

	UPROPERTY()
	FLinearColor m_DefaultColor;

	UPROPERTY()
	int m_Index;

	FKey m_Hotkey;

	UUserWidget* m_pConnectedWidget;

public :
	void InitWidget(const FKey& _Key, int _Index);
	void UpdateWidget();
	void Use();

	/* Get */
	FORCEINLINE const int& GetIndex() const { return m_Index; }

	/* Set */
	FORCEINLINE void SetHotkey(const FKey& _Key) { m_Hotkey = _Key; }

protected :
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;



};
