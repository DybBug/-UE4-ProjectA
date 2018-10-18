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
class UMaterialInstanceDynamic;

UCLASS()
class PROJECTA_API UWidget_HotkeySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	UTextBlock* m_pHotkeyText;

	UPROPERTY()
	UBorder* m_pOutline;

	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UTextBlock* m_pNum;

	UPROPERTY()
	UImage* m_pCooldownImage;

	UPROPERTY()
	UTextBlock* m_pCooldownText;

	UPROPERTY()
	FLinearColor m_DefaultColor;

	UPROPERTY()
	int m_Index;

	UPROPERTY()
	UMaterialInstanceDynamic* m_pDynamicMaterial;

	FKey m_Hotkey;

	UWidget_Hotkey* m_pHotkeyWidget;

	UUserWidget* m_pAssignedWidget;

	float m_Percent;

public:
	void InitWidget(UWidget_Hotkey* _pWidget, const FKey& _Key, int _Index);
	void UpdateWidget();
	void Use();

	void UpdateCooldown(float _Percent);
	void ActivateCooldown();
	void DetactiveCooldown();

	/* Get */
	FORCEINLINE const int& GetIndex() const { return m_Index; }


	FORCEINLINE UUserWidget* const& GetAssignedWidget() const { return m_pAssignedWidget; }

	/* Set */
	FORCEINLINE void SetHotkey(const FKey& _Key) { m_Hotkey = _Key; }

	FORCEINLINE void SetAssignedWidget(UUserWidget* _pWidget) { m_pAssignedWidget = _pWidget; }


protected :
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;



};
