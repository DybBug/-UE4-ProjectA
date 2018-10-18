// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/Skill_Base.h"
#include "ProjectA_Enums.h"
#include "Skill_Buff.generated.h"

/**
 * 
 */
class UTimelineComponent;
class UWidget_BuffIcon;

USTRUCT(BlueprintType)
struct FBuff_Stage
{
	GENERATED_BODY()

public :
	// #. 버프 타입.
	UPROPERTY(EditAnywhere, Category = "Buff_Stage")
	EStat_Types BuffType;

	// #. 버프 수치.
	UPROPERTY(EditAnywhere, Category = "Buff_Stage")
	float Value;

	// #. 초당 버프 수치.
	UPROPERTY(EditAnywhere, Category = "Buff_Stage")
	float ValuePerSecond;

	// #. 지속 시간.
	UPROPERTY(EditAnywhere, Category = "Buff_Stage")
	float DurationTime;
};


UCLASS()
class PROJECTA_API ASkill_Buff : public ASkill_Base
{
	GENERATED_BODY()

public :
	ASkill_Buff();

protected :
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TArray<FBuff_Stage> m_BuffStages;
	
	UTimelineComponent* m_pTimeline;

	UWidget_BuffIcon* m_pBuffIconWidget;

	float m_AppliedValue;

public :
	virtual void Use() override;
	void Reset();

	/* Get */
	FORCEINLINE const FBuff_Stage& GetBuffStageAt(int i) const { return m_BuffStages[i]; }

	/* Set */
	FORCEINLINE void SetBuffIconWidget(UWidget_BuffIcon* _pWidget) { m_pBuffIconWidget = _pWidget; }

protected :
	void _ApplyBuff(EStat_Types _Type, float _Value);

	virtual void _CastingFinish() override;

	UFUNCTION()
	void _Tick();

	UFUNCTION()
	void _Finish();
	
};
