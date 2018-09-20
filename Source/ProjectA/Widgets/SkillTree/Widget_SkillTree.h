// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_Base.h"
#include "Widget_SkillTree.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
class UWidget_Main;
class UComponent_Skill;

UCLASS()
class PROJECTA_API UWidget_SkillTree : public UWidget_Base
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
protected :
	UPROPERTY()
	UButton* m_pCloseButton;
	
	UComponent_Skill* m_pSkill;
	
public :
	void InitWidget(UWidget_Main* _pMain, UComponent_Skill* _pSkill);

protected :
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

private:
	UFUNCTION()
	void _OnCloseButtonClicked();


};
