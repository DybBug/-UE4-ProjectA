// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SkillCategory.generated.h"

/**
 * 
 */
class USizeBox;
class UBorder;
class UCanvasPanel;
class UWidget_SkillTree;
class UWidget_SkillEntry;

UCLASS()
class PROJECTA_API UWidget_SkillCategory : public UUserWidget
{
	GENERATED_BODY()

protected :
	virtual void NativePreConstruct() override;
	
protected :
	UPROPERTY()
	USizeBox* m_pSize;

	UPROPERTY()
	UBorder* m_pBorder;

	UPROPERTY()
	UCanvasPanel* m_pEntryList;

	UWidget_SkillTree* m_pSkillTreeWidget;

public :
	void InitWidget(UWidget_SkillTree* _pWidget);
	void UpdateWidget();
};
