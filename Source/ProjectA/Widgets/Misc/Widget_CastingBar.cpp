// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_CastingBar.h"

#include <Components/ProgressBar.h>


void UWidget_CastingBar::UpdateWidget(float _Percent)
{
	m_pProgressBar->SetPercent(_Percent);
}
