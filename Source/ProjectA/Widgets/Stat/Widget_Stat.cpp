// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Stat.h"
#include "Widget_StatEntry.h"
#include "Components/Component_Stat.h"

#include <Components/VerticalBox.h>
#include <Components/Button.h>
#include <Components/TextBlock.h>


void UWidget_Stat::NativeConstruct()
{
	m_pCloseButton->OnClicked.AddDynamic(this, &UWidget_Stat::_OnCloseButtonClicked);
	m_pApplyButton->OnClicked.AddDynamic(this, &UWidget_Stat::_OnApplyButtonClicked);
	m_pCancelButton->OnClicked.AddDynamic(this, &UWidget_Stat::_OnCancelButtonClicked);
}

void UWidget_Stat::InitWidget(UWidget_Main* _pMainWidget, UComponent_Stat* _pStat)
{
	UWidget_Base::InitWidget(_pMainWidget);

	m_pStat = _pStat;

	m_StatPoint = 0;
	m_UsedStatPoint = 0;
}

void UWidget_Stat::UpdateWidget(int _Point)
{
	m_StatPoint = _Point;

	m_pStatPointText->SetText(FText::AsNumber(m_StatPoint));

	for (int i = 0; i < m_pStatList->GetChildrenCount(); ++i)
	{
		UWidget_StatEntry* pEntryWidget = Cast<UWidget_StatEntry>(m_pStatList->GetChildAt(i));
		pEntryWidget->UpdateButtons();
		pEntryWidget->UpdateStatColor();
	}	
}


void UWidget_Stat::ModifyStatPoint(int _Value)
{
	m_StatPoint += _Value;
	m_UsedStatPoint  -= _Value;

	m_StatPoint = FMath::Clamp<int>(m_StatPoint, 0,  m_pStat->GetStatPoint());
	m_UsedStatPoint = FMath::Clamp<int>(m_UsedStatPoint, 0, m_pStat->GetStatPoint());

	UpdateWidget(m_StatPoint);
}


void UWidget_Stat::GenerateStatEntries()
{
	m_pStatList->ClearChildren();

	if (m_pStat && m_EntryWidgetClass)
	{
		for (auto Stat : m_pStat->GetStats())
		{
			UWidget_StatEntry* pEntryWidget = CreateWidget<UWidget_StatEntry>(GetWorld(), m_EntryWidgetClass);
			FString Name = CONVERT_DISPLAYNAME_TO_STRING(L"EStat_Types", Stat.Key);
			pEntryWidget->InitWidget(Stat.Key, m_pStat);
			pEntryWidget->UpdateWidget(Stat.Value);
			m_pStat->SetEntryWidget(pEntryWidget);
			
			m_pStatList->AddChildToVerticalBox(pEntryWidget);
		}
	}
}

void UWidget_Stat::_OnCloseButtonClicked()
{
	if (m_pStat)
	{
		_OnCancelButtonClicked();
		m_pStat->Close();
	}
}


void UWidget_Stat::_OnApplyButtonClicked()
{
	for (int i = 0; i < m_pStatList->GetChildrenCount(); ++i)
	{
		UWidget_StatEntry* pEntryWidget = Cast<UWidget_StatEntry>(m_pStatList->GetChildAt(i));
		m_pStat->SetStat(pEntryWidget->GetStatType(), pEntryWidget->GetStatInfo());

		pEntryWidget->UpdateButtons();
		pEntryWidget->UpdateStatColor();
	}

	m_pStat->ModifyStatPoint(-m_UsedStatPoint);
	m_UsedStatPoint =  0;
}

void UWidget_Stat::_OnCancelButtonClicked()
{
	for (int i = 0; i < m_pStatList->GetChildrenCount(); ++i)
	{
		UWidget_StatEntry* pEntryWidget = Cast<UWidget_StatEntry>(m_pStatList->GetChildAt(i));
		pEntryWidget->ResetStat();
	}

	ModifyStatPoint(m_UsedStatPoint);
}


