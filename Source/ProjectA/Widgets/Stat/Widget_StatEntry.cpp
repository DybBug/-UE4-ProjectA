// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_StatEntry.h"
#include "Widget_Stat.h"

#include <Components/TextBlock.h>
#include <Components/Button.h>

#define LOCTEXT_NAMESPACE "Format"

void UWidget_StatEntry::NativeConstruct()
{
	m_pPlusButton->SetVisibility(ESlateVisibility::Hidden);
	m_pMinusButton->SetVisibility(ESlateVisibility::Hidden);

	m_pPlusButton->OnClicked.AddDynamic(this, &UWidget_StatEntry::_OnPlusButtonClicked);
	m_pMinusButton->OnClicked.AddDynamic(this, &UWidget_StatEntry::_OnMinusButtonClicked);
}


void UWidget_StatEntry::InitWidget(const EStat_Types& _Type, UComponent_Stat* _pStat)
{
	m_StatType = _Type;
	m_pStat = _pStat;

	m_StatInfo = m_pStat->GetStat(m_StatType);

	if (m_StatInfo.MaxValue <= 0.f)
	{
		m_pMaxText->SetVisibility(ESlateVisibility::Collapsed);
		m_pSlashText->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		m_pMaxText->SetText(FText::AsNumber(m_StatInfo.MaxValue));

		m_pMaxText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_pSlashText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	FString Name = CONVERT_DISPLAYNAME_TO_STRING(L"EStat_Types", _Type);
	m_pStatText->SetText(FText::FromString(Name));

	m_pCurrentText->SetText(FText::AsNumber(m_StatInfo.CurrentValue));
}

void UWidget_StatEntry::UpdateWidget(const FStat_Info& _StatInfo)
{	
	m_StatInfo = _StatInfo;

	if (m_StatInfo.MaxValue <= 0.f)
	{
		m_pMaxText->SetVisibility(ESlateVisibility::Collapsed);
		m_pSlashText->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		m_pMaxText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_pSlashText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		m_pMaxText->SetText(FText::AsNumber(m_StatInfo.MaxValue));
	}

	m_pCurrentText->SetText(FText::AsNumber(m_StatInfo.CurrentValue));
}

void UWidget_StatEntry::UpdateButtons()
{
	_UpdatePlusButton();
	_UpdateMinusButton();
}

void UWidget_StatEntry::UpdateStatColor()
{
	if (m_StatInfo.MaxValue == 0)
	{
		if (m_StatInfo.CurrentValue > m_pStat->GetStat(m_StatType).CurrentValue)
		{
			m_pCurrentText->SetColorAndOpacity(FLinearColor::Green);
		}
		else
		{
			m_pCurrentText->SetColorAndOpacity(FLinearColor::White);
		}
	}
	else
	{
		if (m_StatInfo.MaxValue > m_pStat->GetStat(m_StatType).MaxValue)
		{
			m_pMaxText->SetColorAndOpacity(FLinearColor::Green);
		}
		else
		{
			m_pMaxText->SetColorAndOpacity(FLinearColor::White);
		}
	}
}

void UWidget_StatEntry::ResetStat()
{
	UpdateWidget(m_pStat->GetStat(m_StatType));
}

void UWidget_StatEntry::OnActivePlusButton(bool _bActive, ESlateVisibility _Visibility)
{
	if (m_StatInfo.IncreasePerPoint == 0.f)
	{
		m_pPlusButton->SetVisibility(ESlateVisibility::Hidden);
		m_pPlusButton->SetIsEnabled(false);
		return;
	}

	m_pPlusButton->SetVisibility(_Visibility);
	m_pPlusButton->SetIsEnabled(_bActive);
}

 void UWidget_StatEntry::OnActiveMinusButton(bool _bActive, ESlateVisibility _Visibility)
{
	if (m_StatInfo.IncreasePerPoint == 0.f)
	{
		m_pMinusButton->SetVisibility(ESlateVisibility::Hidden);
		m_pMinusButton->SetIsEnabled(false);
		return;
	}

	m_pMinusButton->SetVisibility(_Visibility);
	m_pMinusButton->SetIsEnabled(_bActive);
}

 void UWidget_StatEntry::_IncreaseStat()
 {
	 if (m_StatInfo.MaxValue <= 0.f)
	 {
		 m_StatInfo.CurrentValue += m_StatInfo.IncreasePerPoint;
	 }
	 else
	 {
		 m_StatInfo.MaxValue += m_StatInfo.IncreasePerPoint;

		 m_pMaxText->SetText(FText::AsNumber(m_StatInfo.MaxValue));
	 }

	 m_pCurrentText->SetText(FText::AsNumber(m_StatInfo.CurrentValue));
 }

 void UWidget_StatEntry::_DecreaseStat()
 {
	 if (m_StatInfo.MaxValue <= 0.f)
	 {
		 m_StatInfo.CurrentValue -= m_StatInfo.IncreasePerPoint;
	 }
	 else
	 {
		 m_StatInfo.MaxValue -= m_StatInfo.IncreasePerPoint;

		 m_pMaxText->SetText(FText::AsNumber(m_StatInfo.MaxValue));
	 }

	 m_pCurrentText->SetText(FText::AsNumber(m_StatInfo.CurrentValue));
 }

 void UWidget_StatEntry::_UpdatePlusButton()
 {
	if (m_pStat->GetStatWidget()->GetStatPoint() == 0)
	{
		OnActivePlusButton(false, ESlateVisibility::Visible);
	}
	else
	{
		OnActivePlusButton(true, ESlateVisibility::Visible);
	}

 }

 void UWidget_StatEntry::_UpdateMinusButton()
 {
	if (m_StatInfo.MaxValue == 0)
	{
		if (m_StatInfo.CurrentValue == m_pStat->GetStat(m_StatType).CurrentValue)
		{
			OnActiveMinusButton(false, ESlateVisibility::Visible);
		}
		else
		{
			OnActiveMinusButton(true, ESlateVisibility::Visible);
		}
	}
	else
	{
		if (m_StatInfo.MaxValue == m_pStat->GetStat(m_StatType).MaxValue)
		{
			OnActiveMinusButton(false, ESlateVisibility::Visible);
		}
		else
		{
			OnActiveMinusButton(true, ESlateVisibility::Visible);
		}
	}	 
 }

void UWidget_StatEntry::_OnPlusButtonClicked()
{	
	_IncreaseStat();

	m_pStat->GetStatWidget()->ModifyStatPoint(-1);
}

void UWidget_StatEntry::_OnMinusButtonClicked()
{
	_DecreaseStat();

	m_pStat->GetStatWidget()->ModifyStatPoint(1);
}

#undef LOCTEXT_NAMESPACE

