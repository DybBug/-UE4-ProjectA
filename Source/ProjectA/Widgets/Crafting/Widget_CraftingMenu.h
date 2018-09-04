// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_CraftingMenu.generated.h"

/**
 * 
 */
class UVerticalBox;
class UWidget_CraftingEntry;

UCLASS()
class PROJECTA_API UWidget_CraftingMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	UPROPERTY()
	UVerticalBox* m_pCraftingEntryList;

public :
	void InitWidget();

	FORCEINLINE void AddCraftingEntryWidget(UWidget_CraftingEntry* _pEntry);
	
	
};
