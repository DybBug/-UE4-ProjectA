// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_DeadEnd.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UNotify_DeadEnd : public UAnimNotify
{
	GENERATED_BODY()

private :
	virtual void Notify(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation) override;
	
};
