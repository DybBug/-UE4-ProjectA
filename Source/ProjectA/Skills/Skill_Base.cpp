// Fill out your copyright notice in the Description page of Project Settings.

#include "Skill_Base.h"
#include "Players/Player_Character.h"
#include "Components/Component_SkillTree.h"

#include <Animation/AnimMontage.h>
#include <Components/TimelineComponent.h>
#include <Kismet/KismetSystemLibrary.h>


// Sets default values
ASkill_Base::ASkill_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	m_bIsUsing = false;

	m_pSkillTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SkillTimeline"));
}

// Called when the game starts or when spawned
void ASkill_Base::BeginPlay()
{
	Super::BeginPlay();

	if (m_Info.pAnimMontage)
	{
		FOnTimelineEventStatic TimelineEvent;
		TimelineEvent.BindUFunction(this, "_FinishSkill");

		m_pSkillTimeline->SetTimelineFinishedFunc(TimelineEvent);
		m_pSkillTimeline->SetTimelineLength(m_Info.pAnimMontage->SequenceLength * 0.8f);
		m_pSkillTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	}
}

void ASkill_Base::Use(UComponent_SkillTree* _pSkill)
{
	m_pSkill = _pSkill;
	m_bIsUsing = true;

	APlayer_Character* pPlayer = Cast<APlayer_Character>(_pSkill->GetOwner());
	float Duration = pPlayer->PlayAnimMontage(m_Info.pAnimMontage);

	m_pSkillTimeline->PlayFromStart();
}

void  ASkill_Base::Upgrade()
{
	m_Info.CurrentLevel += 1;
	m_Info.CurrentLevel = FMath::Clamp(m_Info.CurrentLevel, 0, m_Info.MaxLevel);
}

void  ASkill_Base::Downgrade()
{
	m_Info.CurrentLevel -= 1;
	m_Info.CurrentLevel = FMath::Clamp(m_Info.CurrentLevel, 0, m_Info.MaxLevel);
}

void ASkill_Base::_FinishSkill()
{
	if (m_pSkill)
	{
		m_pSkill->FinishSkill();
		m_bIsUsing = false;
		m_pSkill = nullptr;
	}
}


