// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SkillCategory.h"
#include "Widget_SkillEntry.h"
#include "Widget_SkillTree.h"

#include <Components/SizeBox.h>
#include <Components/Border.h>
#include <Components/CanvasPanel.h>

void UWidget_SkillCategory::NativePreConstruct()
{
	
}

void UWidget_SkillCategory::InitWidget(UWidget_SkillTree* _pWidget)
{
	m_pSkillTreeWidget = _pWidget;
	for (int i = 0; i < m_pEntryList->GetChildrenCount(); ++i)
	{
		UWidget_SkillEntry* pEntry = Cast<UWidget_SkillEntry>(m_pEntryList->GetChildAt(i));
		pEntry->InitWidget(m_pSkillTreeWidget);
	}
}

void UWidget_SkillCategory::UpdateWidget()
{
	for (int i = 0; i < m_pEntryList->GetChildrenCount(); ++i)
	{
		UWidget_SkillEntry* pEntry = Cast<UWidget_SkillEntry>(m_pEntryList->GetChildAt(i));
		pEntry->UpdateWidget();
	}
}



