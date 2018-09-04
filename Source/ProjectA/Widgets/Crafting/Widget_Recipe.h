// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Recipe.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;

class AItem_Base;

UCLASS()
class PROJECTA_API UWidget_Recipe : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UTextBlock* m_pAmountText;

	const AItem_Base* m_pRecipeItem;
	int m_CurrentAmount;
	int m_MaxAmount;
	
public :
	void InitWidget(const AItem_Base* const& _pRecipeItem, int _Amount);
	void UpdateWidget();
	
	bool IsAmountEnough();
};
