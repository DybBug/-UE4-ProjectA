// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SkillTree.h"
#include "Widgets/Widget_Main.h"
#include "Components/Component_Skill.h"

#include <Components/Button.h>

void UWidget_SkillTree::NativeConstruct()
{
	m_pCloseButton->OnClicked.AddDynamic(this, &UWidget_SkillTree::_OnCloseButtonClicked);
}

void UWidget_SkillTree::InitWidget(UWidget_Main* _pMain, UComponent_Skill* _pSkill)
{
	UWidget_Base::InitWidget(_pMain);
	m_pSkill = _pSkill;
}

FReply UWidget_SkillTree::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidget_Base::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}

	return FReply::Unhandled();
}

bool UWidget_SkillTree::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return false;
}

void UWidget_SkillTree::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	return UWidget_Base::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UWidget_SkillTree::_OnCloseButtonClicked()
{
	if (m_pSkill)
	{
		m_pSkill->Close();
	}
}



