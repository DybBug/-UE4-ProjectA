// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Component_Base.h"
#include "Component_SkillTree.generated.h"

class ASkill_Base;
class UTimelineComponent;
class UWidget_SkillTree;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_SkillTree : public UComponent_Base
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_SkillTree();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected :	
	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TArray<ASkill_Base*> m_SkillList;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	int m_Combo;

	UPROPERTY()
	UTimelineComponent* m_pComboTimeline;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	int m_SkillPoint;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	int m_MaxCombo;

public :
	virtual void InitComponent(UWidget_Base* _pWidget) override;
	virtual void UpdateComponent() override;

	void AddSkillPoint(int _Value);
	void AddSkill(ASkill_Base* _pSkill, int _Index);
	void RemoveSkill(int _Index);

	void UseSkill();
	void FinishSkill();
	void PlayResetCombo();
	void StopResetCombo();

	// #. Return 
	// 0이상 : 인덱스.
	// -1 : 존재하지 않음.
	int HasSkill_In_SkillList(TSubclassOf<ASkill_Base> _SkillClass);

	/* Get */
	FORCEINLINE const int& GetSkillPoint() const { return m_SkillPoint; }
	FORCEINLINE const int& GetMaxCombo() const { return m_MaxCombo; }

	FORCEINLINE ASkill_Base* const& GetSkill(int _Index) { return m_SkillList[_Index]; }

private :
	UFUNCTION()
	void _ResetCombo();


};
