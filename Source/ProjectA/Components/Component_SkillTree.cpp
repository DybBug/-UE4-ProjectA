// Fill out your copyright notice in the Description page of Project Settings.

#include "Component_SkillTree.h"
#include "Skills/Skill_Base.h"
#include "Players/Player_Character.h"
#include "Widgets/SkillTree/Widget_SkillTree.h"

#include <TimerManager.h>
#include <Engine/World.h>
#include <Components/TimelineComponent.h>
#include <Kismet/KismetSystemLibrary.h>


// Sets default values for this component's properties
UComponent_SkillTree::UComponent_SkillTree()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	m_pComboTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ComboTimeline"));

	m_bIsOpen = false;
	m_MaxCombo = 0;
	m_Combo = 0;
	m_SkillPoint = 1;
}

// Called when the game starts
void UComponent_SkillTree::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FOnTimelineEventStatic TimelineEvent;
	TimelineEvent.BindUFunction(this, "_ResetCombo");

	m_pComboTimeline->SetTimelineFinishedFunc(TimelineEvent);
	m_pComboTimeline->SetTimelineLength(1.5f);
	m_pComboTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);	
}

void UComponent_SkillTree::InitComponent(UWidget_Base* _pWidget)
{
	UComponent_Base::InitComponent(_pWidget);

	int Count = Cast<UWidget_SkillTree>(_pWidget)->GetComboCount();
	m_SkillList.SetNum(Count);
}

void UComponent_SkillTree::UpdateComponent()
{
	m_pWidget->UpdateWidget();
}

void UComponent_SkillTree::AddSkillPoint(int _Value)
{
	m_SkillPoint += _Value;
	m_pWidget->UpdateWidget();
}

void UComponent_SkillTree::AddSkill(ASkill_Base* _pSkill, int _Index)
{
	if (m_SkillList.IsValidIndex(_Index))
	{
		m_SkillList[_Index] = _pSkill;
		m_MaxCombo++;
	}
}

void UComponent_SkillTree::RemoveSkill(int _Index)
{
	if (m_SkillList.IsValidIndex(_Index))
	{
		m_SkillList[_Index] = nullptr;
		m_MaxCombo--;
	}
}

void UComponent_SkillTree::UseSkill()
{
	if (m_SkillList[m_Combo])
	{
		StopResetCombo();
		APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
		m_SkillList[m_Combo]->Use();
	}
}

void UComponent_SkillTree::FinishSkill()
{
	m_Combo = ((m_Combo + 1) % m_MaxCombo);
	PlayResetCombo();
}

void UComponent_SkillTree::PlayResetCombo()
{
	m_pComboTimeline->PlayFromStart();
}

void UComponent_SkillTree::StopResetCombo()
{
	if (m_pComboTimeline->IsPlaying())
	{
		m_pComboTimeline->Stop();
	}
}
int UComponent_SkillTree::HasSkill_In_SkillList(TSubclassOf<ASkill_Base> _SkillClass)
{
	for (int i = 0; i < m_MaxCombo; ++i)
	{
		if (m_SkillList[i] != nullptr)
		{
			if (m_SkillList[i]->GetClass() == _SkillClass)
			{
				return i;
			}
		}
	}
	return -1;
}

void UComponent_SkillTree::_ResetCombo()
{
	m_Combo = 0;
}

