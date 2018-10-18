// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Skill_Base.h"
#include "Skill_Active.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API ASkill_Active : public ASkill_Base
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(EditAnywhere, Category = "Configuration")
	float Damage = 0.f;
	
public :
	virtual void Use() override;
	
};
