// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill_Base.generated.h"

class UAnimMontage;
class APlayer_Character;
class UTimelineComponent;
class UComponent_Skill;

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
	float Damage = 0.f;
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
	UTimelineComponent* m_pSkillTimeline;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FSkill_Info m_Info;

	UComponent_Skill* m_pSkill;

	bool m_bIsUsing;

public :
	void Use(UComponent_Skill* _pSkill);

	/* Get */
	FORCEINLINE const FSkill_Info& GetInfo() const { return m_Info; }
	FORCEINLINE const bool& GetIsUsing() const { return m_bIsUsing; }

protected :
	UFUNCTION()
	void _FinishSkill();
	
};
