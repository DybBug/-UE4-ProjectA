// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_StatBar.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

#define LOCTEXT_NAMESPACE "Format"

void UWidget_StatBar::NativePreConstruct()
{
	m_pStatBar->SetFillColorAndOpacity(m_FillColor);
}


void UWidget_StatBar::InitWidget(UWidget_Main* _pMainWidget)
{
	m_pMainWidget = _pMainWidget;
}

void UWidget_StatBar::UpdateWidget(int _CurrValue, int _MaxValue)
{
	float Percent = ((float)_CurrValue / (float)_MaxValue);
	m_pStatBar->SetPercent(Percent);

	FText Format = FText::Format(LOCTEXT("Format", "{0}/{1}"), _CurrValue, _MaxValue);
	m_pStatText->SetText(Format);
}

#undef LOCTEXT_NAMESPACE

