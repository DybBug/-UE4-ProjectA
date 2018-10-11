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
	m_UsedStatPoint = 0;
}

// Called when the game starts
void UComponent_Stat::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UComponent_Stat::InitComponent(UWidget_Base* _pWidget)
{
	UComponent_Base::InitComponent(_pWidget);

	m_StatBarWidgets.Empty();
	m_pEntryWidgets.Empty();

	Cast<UWidget_Stat>(m_pWidget)->GenerateStatEntries();
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

void UComponent_Stat::AddStatPoint(float _Value)
{
	m_StatPoint += (_Value + m_UsedStatPoint);
	m_pWidget->UpdateWidget();
}

void UComponent_Stat::ModifyStatPoint(float _Value)
{
	m_StatPoint += _Value;
	m_UsedStatPoint -= _Value;

	m_pWidget->UpdateWidget();
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

void UComponent_Stat::Apply()
{
	m_UsedStatPoint = 0;
}

void UComponent_Stat::Cancel()
{
	m_StatPoint += m_UsedStatPoint;
	m_UsedStatPoint = 0;

	m_pWidget->UpdateWidget();
}

void UComponent_Stat::SetEntryWidget(UWidget_StatEntry* const& _pWidget)
{
	m_pEntryWidgets.Add(_pWidget);
}


