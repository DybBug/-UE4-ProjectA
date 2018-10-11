// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_Base.h"
#include "Widget_Crafting.generated.h"

/**
 * 
 */
class UButton;
class UCanvasPanel;
class UWidgetSwitcher;
class UWidget_Main;
class UWidget_CraftingEntry;
class UWidget_CraftingMenu;
class UWidget_CraftingScreen;
class UComponent_Crafting;

UCLASS()
class PROJECTA_API UWidget_Crafting : public UWidget_Base
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
protected :
	UPROPERTY()
	UButton* m_pCloseButton;

	UPROPERTY()
	UButton* m_pConsumablesButton;

	UPROPERTY()
	UButton* m_pEquipmentButton;

	UPROPERTY()
	UWidgetSwitcher* m_pCraftingMenuList;

	UPROPERTY()
	UWidget_CraftingMenu* m_pConsumablesMenu;

	UPROPERTY()
	UWidget_CraftingMenu* m_pEquipmentMenu;

	UPROPERTY()
	UWidget_CraftingScreen* m_pCraftingScreen;

	UPROPERTY(EditAnywhere,  Category = "Configuration")
	TSubclassOf<UWidget_CraftingEntry> m_EntryWidgetClass;

public :
	virtual void InitWidget(UWidget_Main* _pMain, UComponent_Base* _pComponent) override;
	virtual void UpdateWidget() override;

	void GenerateEntries();

private :
	UFUNCTION()
	void _OnCloseButtonClicked();

	UFUNCTION()
	void _OnConsumablesButtonClicked();

	UFUNCTION()
	void _OnEquipmentButtonClicked();
	
};
