// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_PickupSlot.generated.h"

/**
 * 
 */
class UBorder;
class UImage;
class UTextBlock;
class UComponent_Pickup;
class UWidget_Detail;


UCLASS()
class PROJECTA_API UWidget_PickupSlot : public UUserWidget
{
	GENERATED_BODY()

protected :
	virtual void NativePreConstruct() override;
	
protected :
	UPROPERTY()
	UBorder* m_pBackground;

	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UTextBlock* m_pNameText;

	UPROPERTY()
	UTextBlock* m_pAmountText;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FLinearColor m_DefaultColor;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FLinearColor m_OverlapColor;

	UWidget_Detail* m_pDetailWidget = nullptr;

	UComponent_Pickup* m_pPickup = nullptr;

	int m_Index;

public :
	void InitWidget(UComponent_Pickup* _pPickup, int _Index, UWidget_Detail* _pDetail);

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	
};
