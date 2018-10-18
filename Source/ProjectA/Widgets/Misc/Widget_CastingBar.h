// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_CastingBar.generated.h"

/**
 * 
 */
class UProgressBar;
class UWidget_Main;

UCLASS()
class PROJECTA_API UWidget_CastingBar : public UUserWidget
{
	GENERATED_BODY()

protected :
	UPROPERTY()
	UProgressBar* m_pProgressBar;	

public :	
	void UpdateWidget(float _Percent);
	
};
