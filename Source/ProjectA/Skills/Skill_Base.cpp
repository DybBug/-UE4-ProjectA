// Fill out your copyright notice in the Description page of Project Settings.

#include "Skill_Base.h"
#include "Players/Player_Character.h"
#include "Components/Component_SkillTree.h"
#include "Widgets/Widget_Main.h"
#include "Widgets/Misc/Widget_CastingBar.h"
#include "Widgets/Hotkey/Widget_HotkeySlot.h"

#include <Animation/AnimMontage.h>
#include <Components/TimelineComponent.h>
#include <Kismet/KismetSystemLibrary.h>


// Sets default values
ASkill_Base::ASkill_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	m_bOnAnimation = false;
	m_bOnCasting = false;
	m_bOnCooldown = false;

	m_pAnimationTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("AnimationTimeline"));
	m_pCastingTimeline   = CreateDefaultSubobject<UTimelineComponent>(TEXT("CastingTimelilne"));
	m_pCooldownTimeline  = CreateDefaultSubobject<UTimelineComponent>(TEXT("CooldownTimeline"));
}

// Called when the game starts or when spawned
void ASkill_Base::BeginPlay()
{
	Super::BeginPlay();

	_SetupTimelines();
}

void ASkill_Base::InitSkill(UComponent_SkillTree* _SkillTree)
{
	m_pSkillTree = _SkillTree;
	m_pPlayer = Cast<APlayer_Character>(m_pSkillTree->GetOwner());
}

void ASkill_Base::Use()
{
	if (!m_bOnAnimation && !m_bOnCasting && !m_bOnCooldown)
	{	
		AnimationStart();		
		CastingStart();
	}
}

void  ASkill_Base::Upgrade()
{
	m_Info.CurrentLevel += 1;
	m_Info.CurrentLevel = FMath::Clamp(m_Info.CurrentLevel, 0, m_Info.MaxLevel);

	if (m_pHotkeySlotWidget)
	{
		m_pHotkeySlotWidget->UpdateWidget();
	}
}

void  ASkill_Base::Downgrade()
{
	m_Info.CurrentLevel -= 1;
	m_Info.CurrentLevel = FMath::Clamp(m_Info.CurrentLevel, 0, m_Info.MaxLevel);

	if (m_pHotkeySlotWidget)
	{
		m_pHotkeySlotWidget->UpdateWidget();
	}
}

void ASkill_Base::AnimationStart()
{
	if (m_Info.pAnimMontage)
	{
		m_bOnAnimation = true;
		float Duration = m_pPlayer->PlayAnimMontage(m_Info.pAnimMontage);

		m_pAnimationTimeline->PlayFromStart();
	}
}

void ASkill_Base::CastingStart()
{
	m_bOnCasting = true;
	m_pCastingTimeline->PlayFromStart();
}

void ASkill_Base::CooldownStart()
{
	m_bOnCooldown = true;
	m_pCooldownTimeline->PlayFromStart();
}

void ASkill_Base::_SetupTimelines()
{
	FOnTimelineEvent TimelineEvent;

	// #. 애니메이션 타임라인 설정.
	if (m_Info.pAnimMontage)
	{
		TimelineEvent.BindUFunction(this, "_AnimationFinish");
		m_pAnimationTimeline->SetTimelineFinishedFunc(TimelineEvent);

		m_pAnimationTimeline->SetTimelineLength(m_Info.pAnimMontage->SequenceLength * 0.8f);
		m_pAnimationTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	}

	// #. 캐스팅 타임라인 설정.
	if (m_Info.CastingTime > 0.f)
	{
		TimelineEvent.BindUFunction(this, "_CastingTick");
		m_pCastingTimeline->SetTimelinePostUpdateFunc(TimelineEvent);

		TimelineEvent.BindUFunction(this, "_CastingFinish");
		m_pCastingTimeline->SetTimelineFinishedFunc(TimelineEvent);

		m_pCastingTimeline->SetTimelineLength(m_Info.CastingTime);
		m_pCastingTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	}

	// #. 쿨다운 타임라인 설정.
	if (m_Info.CooldownTime > 0.f)
	{
		TimelineEvent.BindUFunction(this, "_CooldownTick");
		m_pCooldownTimeline->SetTimelinePostUpdateFunc(TimelineEvent);

		TimelineEvent.BindUFunction(this, "_CooldownFinish");
		m_pCooldownTimeline->SetTimelineFinishedFunc(TimelineEvent);

		m_pCooldownTimeline->SetTimelineLength(m_Info.CooldownTime);
		m_pCooldownTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	}

}

void ASkill_Base::_AnimationFinish()
{
	if (m_pSkillTree)
	{
		m_pSkillTree->FinishSkill();
		m_bOnAnimation = false;
	}
}

void  ASkill_Base::_CastingTick()
{

	m_pPlayer->GetMainWidget()->GetCastingBarWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	float Percent = m_pCastingTimeline->GetPlaybackPosition() / m_pCastingTimeline->GetTimelineLength();

	m_pPlayer->GetMainWidget()->GetCastingBarWidget()->UpdateWidget(Percent);
}

void  ASkill_Base::_CastingFinish()
{
	m_bOnCasting = false;

	m_pPlayer->GetMainWidget()->GetCastingBarWidget()->SetVisibility(ESlateVisibility::Hidden);
	m_pPlayer->GetMainWidget()->GetCastingBarWidget()->UpdateWidget(0.f);

	CooldownStart();
}

void  ASkill_Base::_CooldownTick()
{
	if (m_pHotkeySlotWidget)
	{
		m_pHotkeySlotWidget->ActivateCooldown();
		float Percent = m_pCooldownTimeline->GetPlaybackPosition() / m_pCooldownTimeline->GetTimelineLength();
		m_pHotkeySlotWidget->UpdateCooldown(Percent);
	}
}

void  ASkill_Base::_CooldownFinish()
{
	m_bOnCooldown = false;

	if (m_pHotkeySlotWidget)
	{
		m_pHotkeySlotWidget->DetactiveCooldown();
	}
}



