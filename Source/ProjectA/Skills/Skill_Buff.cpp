// Fill out your copyright notice in the Description page of Project Settings.

#include "Skill_Buff.h"
#include "Players/Player_Character.h"
#include "Widgets/Misc/Widget_BuffIcon.h"
#include "Components/Component_Stat.h"

#include <Components/TimelineComponent.h>

ASkill_Buff::ASkill_Buff()
{
	FOnTimelineEvent Event;

	m_pTimeline = CreateDefaultSubobject<UTimelineComponent>("Timeline");
	m_pTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);

	Event.BindUFunction(this, "_Tick");
	m_pTimeline->SetTimelinePostUpdateFunc(Event);

	Event.BindUFunction(this, "_Finish");
	m_pTimeline->SetTimelineFinishedFunc(Event);
}

void ASkill_Buff::Use()
{
	if (!m_bOnCooldown)
	{
		CastingStart();
	}
}

void ASkill_Buff::Reset()
{
	if(m_pTimeline->IsPlaying())
	{
		m_pTimeline->Stop();

		EStat_Types Type = m_BuffStages[m_Info.CurrentLevel - 1].BuffType;
		_ApplyBuff(Type, -m_AppliedValue);

		m_pTimeline->PlayFromStart();
	}
}

void ASkill_Buff::_ApplyBuff(EStat_Types _Type, float _Value)
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(m_pCaster);

	if (pPlayer)
	{
		if (pPlayer->GetStat()->GetStat(_Type).MaxValue > 0.f)
		{
			pPlayer->GetStat()->ModifyMaxValueByType(_Type, _Value);

			if (pPlayer->GetStat()->GetStat(_Type).CurrentValue <= pPlayer->GetStat()->GetStat(_Type).MaxValue)
			{
				return;
			}
		}

		pPlayer->GetStat()->ModifyCurrentValueByType(_Type, _Value);
	}
}

void ASkill_Buff::_CastingFinish()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(m_pCaster);
	if (pPlayer)
	{
		if (m_BuffStages.Num() > 0)
		{
			float DurationTime = m_BuffStages[m_Info.CurrentLevel - 1].DurationTime;
			m_pTimeline->SetTimelineLength(DurationTime);
			m_pTimeline->PlayFromStart();

			pPlayer->GetStat()->AddBuff(this);

			EStat_Types Type = m_BuffStages[m_Info.CurrentLevel - 1].BuffType;
			m_AppliedValue = m_BuffStages[m_Info.CurrentLevel - 1].Value;
			_ApplyBuff(Type, m_AppliedValue);
		}

		ASkill_Base::_CastingFinish();
	}
}

void ASkill_Buff::_Tick()
{
	//EStat_Types Type = m_BuffStages[m_Info.CurrentLevel - 1].BuffType;
	//float ValuePerSecond = m_BuffStages[m_Info.CurrentLevel - 1].ValuePerSecond;

	//if (m_pPlayer->GetStat()->GetStat(Type).CurrentValue < m_pPlayer->GetStat()->GetStat(Type).MaxValue)
	//{
	//	ValuePerSecond *= GetWorld()->GetDeltaSeconds();
	//	m_pPlayer->GetStat()->ModifyCurrentValueByType(Type, ValuePerSecond);
	//}

	if (m_pBuffIconWidget)
	{
		float Percent = m_pTimeline->GetPlaybackPosition() / m_pTimeline->GetTimelineLength();
		m_pBuffIconWidget->UpdateWidget(Percent);
	}
}

void ASkill_Buff::_Finish()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(m_pCaster);
	if (pPlayer)
	{
		EStat_Types Type = m_BuffStages[m_Info.CurrentLevel - 1].BuffType;
		_ApplyBuff(Type, -m_AppliedValue);

		pPlayer->GetStat()->RemoveBuff(this);
		m_pBuffIconWidget = nullptr;
	}
}



