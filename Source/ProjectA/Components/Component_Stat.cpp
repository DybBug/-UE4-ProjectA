// Fill out your copyright notice in the Description page of Project Settings.

#include "Component_Stat.h"
#include "Widgets/Stat/Widget_Stat.h"
#include "Widgets/Stat/Widget_StatEntry.h"
#include "Widgets/Misc/Widget_StatBar.h"
#include "Items/Item_Potion.h"


// Sets default values for this component's properties
UComponent_Stat::UComponent_Stat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	for (int i = 0; i < (int)EStat_Types::Max; ++i)
	{
		m_Stats.Add(EStat_Types(i), FStat_Info());
	}

	m_StatPoint = 0;
	m_bIsOpen = false;
}



// Called when the game starts
void UComponent_Stat::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


void UComponent_Stat::InitComponent(UWidget_Stat* _pWidget)
{
	m_StatBarWidgets.Empty();
	m_pEntryWidgets.Empty();

	m_pStatWidget = _pWidget;
	m_pStatWidget->GenerateStatEntries();
}

bool UComponent_Stat::AddWidget(EStat_Types _Type, UWidget_StatBar* const _pWidget)
{
	if (!m_StatBarWidgets.Contains(_Type))
	{
		m_StatBarWidgets.Add(_Type, _pWidget);
		return true;
	}
	return false;
}

void UComponent_Stat::Open()
{
	if (!m_bIsOpen)
	{
		m_bIsOpen = true;
		m_pStatWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UComponent_Stat::Close()
{
	if (m_bIsOpen)
	{
		m_bIsOpen = false;
		m_pStatWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UComponent_Stat::ModifyStatPoint(float _Value)
{
	m_StatPoint += _Value;
	m_pStatWidget->UpdateWidget(m_StatPoint);
}

void UComponent_Stat::ModifyMaxValueByType(const EStat_Types& _Type, float _Value)
{
	m_Stats[_Type].MaxValue += _Value;
	if (m_pEntryWidgets.IsValidIndex((uint8)_Type))
	{
		m_pEntryWidgets[(uint8)_Type]->UpdateWidget(m_Stats[_Type]);
	}
}

void UComponent_Stat::ModifyCurrentValueByType(const EStat_Types& _Type, float _Value)
{
	m_Stats[_Type].CurrentValue += _Value;
	if (m_pEntryWidgets.IsValidIndex((uint8)_Type))
	{
		m_pEntryWidgets[(uint8)_Type]->UpdateWidget(m_Stats[_Type]);
	}
}

void UComponent_Stat::ModifyIncreasePerLevelUpByType(const EStat_Types& _Type, float _Value)
{
	m_Stats[_Type].IncreasePerLevelUp += _Value;
	if (m_pEntryWidgets.IsValidIndex((uint8)_Type))
	{
		m_pEntryWidgets[(uint8)_Type]->UpdateWidget(m_Stats[_Type]);
	}
}

void UComponent_Stat::ModifyIncreasePerPointByType(const EStat_Types& _Type, float _Value)
{
	m_Stats[_Type].IncreasePerPoint += _Value;
	if (m_pEntryWidgets.IsValidIndex((uint8)_Type))
	{
		m_pEntryWidgets[(uint8)_Type]->UpdateWidget(m_Stats[_Type]);
	}
}

void UComponent_Stat::SetEntryWidget(UWidget_StatEntry* const& _pWidget)
{
	m_pEntryWidgets.Add(_pWidget);
}


