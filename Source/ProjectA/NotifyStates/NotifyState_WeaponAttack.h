// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_WeaponAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UNotifyState_WeaponAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	
	virtual void NotifyBegin(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, float _TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation) override;
	
	
};
