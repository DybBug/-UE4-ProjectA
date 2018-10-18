// Fill out your copyright notice in the Description page of Project Settings.

#include "Skill_Active.h"

void ASkill_Active::Use()
{
	if (!m_bOnAnimation)
	{
		AnimationStart();
	}
}




