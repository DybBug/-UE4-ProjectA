// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Detail.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;
class UVerticalBox;
class UWidget_Main;
class AItem_Base;

UCLASS()
class PROJECTA_API UWidget_Detail : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	UPROPERTY()
	UImage* m_pIcon = nullptr;

	UPROPERTY()
	UTextBlock* m_pNameText = nullptr;

	UPROPERTY()
	UTextBlock* m_pDescriptionText = nullptr;

	UPROPERTY()
	UVerticalBox* m_pAbilityContain = nullptr;

	UPROPERTY()
	UVerticalBox* m_pAbilityList = nullptr;

	UWidget_Main* m_pMainWidget = nullptr;

public :
	void InitWidget(UWidget_Main* _pWidget);
	void UpdateWidget(TSubclassOf<AItem_Base> _ItemClass);
	
};
