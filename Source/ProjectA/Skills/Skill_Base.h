// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill_Base.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FSkill_Info
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, Category = "Skill_Info")
	UAnimMontage* pAnimMontage;
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
	UPROPERTY(EditAnywhere, Category = "Configuration")
	FSkill_Info m_SkillInfo;


	
	
};
