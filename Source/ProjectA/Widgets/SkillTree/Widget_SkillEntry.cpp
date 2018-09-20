// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SkillEntry.h"
#include "Skills/Skill_Base.h"

#include <Components/Image.h>
#include <Components/Button.h>
#include <Components/VerticalBox.h>

void UWidget_SkillEntry::NativePreConstruct()
{
	if (IsValid(m_SkillClass))
	{
		const FSkill_Info& Info = m_SkillClass.GetDefaultObject()->GetInfo();
		m_pIcon->SetBrushFromTexture(Info.pIcon);
	}
}

void UWidget_SkillEntry::NativeConstruct()
{
	m_pButtonBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UWidget_SkillEntry::_OnPlusButtonClicked()
{

}

void UWidget_SkillEntry::_OnMinusButtonClicked()
{

}




