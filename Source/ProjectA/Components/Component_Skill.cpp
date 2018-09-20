// Fill out your copyright notice in the Description page of Project Settings.

#include "Component_Skill.h"
#include "Skills/Skill_Base.h"
#include "Players/Player_Character.h"
#include "Widgets/SkillTree/Widget_SkillTree.h"

#include <TimerManager.h>
#include <Engine/World.h>
#include <Components/TimelineComponent.h>
#include <Kismet/KismetSystemLibrary.h>


// Sets default values for this component's properties
UComponent_Skill::UComponent_Skill()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	m_pComboTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ComboTimeline"));

	m_bIsOpen = false;
	m_Combo = 0;
}

// Called when the game starts
void UComponent_Skill::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FOnTimelineEventStatic TimelineEvent;
	TimelineEvent.BindUFunction(this, "_ResetCombo");

	m_pComboTimeline->SetTimelineFinishedFunc(TimelineEvent);
	m_pComboTimeline->SetTimelineLength(1.5f);
	m_pComboTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);	
}

bool UComponent_Skill::InitComponent(UWidget_SkillTree* _pWidget)
{
	m_pSkillTreeWidget = _pWidget;
	return true;
}

void UComponent_Skill::Open()
{
	if (!m_bIsOpen)
	{
		m_bIsOpen = true;
		m_pSkillTreeWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UComponent_Skill::Close()
{
	if (m_bIsOpen)
	{
		m_bIsOpen = false;
		m_pSkillTreeWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UComponent_Skill::UseSkill()
{
	if (m_UseableSkillList.IsValidIndex(m_Combo))
	{
		if (!m_UseableSkillList[m_Combo]->GetIsUsing())
		{
			StopResetCombo();
			APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
			m_UseableSkillList[m_Combo]->Use(this);
		}
	}
}

void UComponent_Skill::FinishSkill()
{
	m_Combo = ((m_Combo + 1) % m_MaxCombo);
	PlayResetCombo();
}

void UComponent_Skill::PlayResetCombo()
{
	m_pComboTimeline->PlayFromStart();
}

void UComponent_Skill::StopResetCombo()
{
	if (m_pComboTimeline->IsPlaying())
	{
		m_pComboTimeline->Stop();
	}
}

void UComponent_Skill::AddUseableSkill(TSubclassOf<ASkill_Base> _SkillClass)
{
	/*if (!m_UseableSkillList.Contains(_SkillClass))
	{
		ASkill_Base* pSkill = GetWorld()->SpawnActor<ASkill_Base>(_SkillClass);
		m_UseableSkillList.Add(pSkill);
	}*/
}

void UComponent_Skill::RemoveUseableSkill(TSubclassOf<ASkill_Base> _SkillClass)
{
	for (int i = 0; i < m_UseableSkillList.Num(); ++i)
	{
		if (m_UseableSkillList[i]->GetClass() == _SkillClass)
		{
			m_UseableSkillList[i]->Destroy();
			m_UseableSkillList.RemoveAt(i);
		}
	}
}

void UComponent_Skill::_ResetCombo()
{
	m_Combo = 0;
}

