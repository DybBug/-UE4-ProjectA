// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_CraftingEntry.generated.h"

/**
 * 
 */
class UButton;
class UImage;
class UTextBlock;
class UComponent_Crafting;
class UWidget_CraftingScreen;
class AItem_Base;

UCLASS()
class PROJECTA_API UWidget_CraftingEntry : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	virtual void NativeConstruct() override;

protected :
	UPROPERTY()
	UButton* m_pEntryButton;

	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UTextBlock* m_pNameText;

	UPROPERTY()
	UTextBlock* m_pDescriptionText;

	UPROPERTY()
	UWidget_CraftingScreen* m_pCraftingScreenWidget;

	int m_CraftingItemIndex;
	
public :
	void InitWidget(int _Index, UWidget_CraftingScreen* _pWidget);
	
protected :
	UFUNCTION()
	void _OnEntryButtonClicked();
};
