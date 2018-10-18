// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill_Base.generated.h"

class UAnimMontage;
class APlayer_Character;
class UTimelineComponent;
class UComponent_SkillTree;
class UWidget_HotkeySlot;


USTRUCT(BlueprintType)
struct FSkill_Info
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, Category = "Skill_Info")
	FName Name = TEXT("#Unknown");

	UPROPERTY(EditAnywhere, Category = "Skill_Info")
	UTexture2D* pIcon = nullptr;

	UPROPERTY(EditAnywhere, Category = "Skill_Info")
	UAnimMontage* pAnimMontage = nullptr;

	UPROPERTY(EditAnywhere, Category = "Skill_Info")
	int MaxLevel;

	UPROPERTY(EditAnywhere, Category = "Skill_Info")
	int CurrentLevel;

	UPROPERTY(EditAnywhere, Category = "Skill_Info")
	FText Description;

	UPROPERTY(EditAnywhere, Category = "Skill_Info")
	float CastingTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Skill_Info")
	float CooldownTime = 0.0f;
};



UCLASS()
class PROJECTA_API ASkill_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected :
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UTimelineComponent* m_pAnimationTimeline;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UTimelineComponent* m_pCastingTimeline;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UTimelineComponent* m_pCooldownTimeline;	

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FSkill_Info m_Info;

	UComponent_SkillTree* m_pSkillTree;

	APlayer_Character* m_pPlayer;

	UWidget_HotkeySlot* m_pHotkeySlotWidget;

	bool m_bOnAnimation;
	bool m_bOnCasting;
	bool m_bOnCooldown;

public :
	void InitSkill(UComponent_SkillTree* _SkillTree);
	virtual void Use();
	void Upgrade();
	void Downgrade();

	void AnimationStart();
	void CastingStart();
	void CooldownStart();

	/* Get */
	FORCEINLINE const FSkill_Info& GetInfo() const { return m_Info; }
	FORCEINLINE const bool& GetOnAnimation() const { return m_bOnAnimation; }

	/* Set */
	FORCEINLINE void SetHotkeySlotWidget(UWidget_HotkeySlot* _pWidget) { m_pHotkeySlotWidget = _pWidget; }

protected :
	void _SetupTimelines();

	UFUNCTION()
	virtual void _AnimationFinish();

	UFUNCTION()
	virtual void _CastingTick();

	UFUNCTION()
	virtual void _CastingFinish();

	UFUNCTION()
	virtual void _CooldownTick();

	UFUNCTION()
	virtual void _CooldownFinish();
	
};
