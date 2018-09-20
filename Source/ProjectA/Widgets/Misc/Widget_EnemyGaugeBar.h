// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_EnemyGaugeBar.generated.h"

/**
 * 
 */

class UTextBlock;
class UProgressBar;
class AEnemy_Base;

UCLASS()
class PROJECTA_API UWidget_EnemyGaugeBar : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	UPROPERTY()
	UTextBlock* m_pNameText;

	UPROPERTY()
	UProgressBar* m_pHealthBar;

	AEnemy_Base* m_pEnemy;
	
public :
	void InitWidget(AEnemy_Base* _pEnemy);
	void UpdateWidget();
	
};
