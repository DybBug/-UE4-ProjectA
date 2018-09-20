// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_Skill.generated.h"

class ASkill_Base;
class UTimelineComponent;
class UWidget_SkillTree;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Skill : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Skill();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected :	
	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TArray<ASkill_Base*> m_UseableSkillList;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	int m_Combo;

	UPROPERTY()
	UTimelineComponent* m_pComboTimeline;

	UWidget_SkillTree* m_pSkillTreeWidget;

	const int m_MaxCombo = 3;

	bool m_bIsOpen;

public :
	bool InitComponent(UWidget_SkillTree* _pWidget);
	void Open();
	void Close();

	void UseSkill();
	void FinishSkill();
	void PlayResetCombo();
	void StopResetCombo();

	// #. 사용 가능한 스킬 추가.
	void AddUseableSkill(TSubclassOf<ASkill_Base> _SkillClass);
	void RemoveUseableSkill(TSubclassOf<ASkill_Base> _SkillClass);

private :
	UFUNCTION()
	void _ResetCombo();

};
