// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_StatBar.generated.h"

/**
 * 
 */

class UProgressBar;
class UTextBlock;
class UWidget_Main;

UCLASS()
class PROJECTA_API UWidget_StatBar : public UUserWidget
{
	GENERATED_BODY()

protected :
	virtual void NativePreConstruct() override;
	
protected :
	UPROPERTY()
	UProgressBar* m_pStatBar;

	UPROPERTY()
	UTextBlock* m_pStatText;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FLinearColor m_FillColor;

	//
	//
	//
	UWidget_Main* m_pMainWidget;

public :
	void InitWidget(UWidget_Main* _pMainWidget);
	void UpdateWidget(int _CurrValue, int _MaxValue);
	
};
