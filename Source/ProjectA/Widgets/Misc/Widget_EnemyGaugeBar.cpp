// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_EnemyGaugeBar.h"
#include "Enemies/Enemy_Base.h"

#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>

void UWidget_EnemyGaugeBar::InitWidget(AEnemy_Base* _pEnemy)
{
	m_pEnemy = _pEnemy;

	FName Name = m_pEnemy->GetInfo().Name;
	m_pNameText->SetText(FText::FromName(Name));
}

void UWidget_EnemyGaugeBar::UpdateWidget()
{
	const FEnemy_Info& EnemyInfo = m_pEnemy->GetInfo();
	float Percent = (EnemyInfo.CurrHealth / EnemyInfo.MaxHealth);
	m_pHealthBar->SetPercent(Percent);
}
