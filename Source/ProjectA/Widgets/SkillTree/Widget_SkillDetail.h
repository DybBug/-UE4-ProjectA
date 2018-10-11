// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SkillDetail.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;
struct FSkill_Info;

UCLASS()
class PROJECTA_API UWidget_SkillDetail : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	UPROPERTY()
	UImage * m_pIcon;

	UPROPERTY()
	UTextBlock* m_pNameText;

	UPROPERTY()
	UTextBlock* m_pCurrentAbilityText;

	UPROPERTY()
	UTextBlock* m_pNextAbilityText;

public :
	void UpdateWidget(const FSkill_Info& _SkillInfo);
	
	
};
