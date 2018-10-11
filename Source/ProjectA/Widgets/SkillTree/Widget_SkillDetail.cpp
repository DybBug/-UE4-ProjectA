// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SkillDetail.h"
#include "Skills/Skill_Base.h"

#include <Components/Image.h>
#include <Components/TextBlock.h>

#define LOCTEXT_NAMESPACE "Format"

void UWidget_SkillDetail::UpdateWidget(const FSkill_Info& _SkillInfo)
{
	m_pIcon->SetBrushFromTexture(_SkillInfo.pIcon);

	FText Format = FText::Format(LOCTEXT("Format", "{0}\n(Lv.{1})"), FText::FromName(_SkillInfo.Name), FText::AsNumber(_SkillInfo.CurrentLevel));
	m_pNameText->SetText(Format);
}

#undef LOCTEXT_NAMESPACE

