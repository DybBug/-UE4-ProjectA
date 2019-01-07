// Fill out your copyright notice in the Description page of Project Settings.

#include "NotifyState_Attack.h"

#include <Components/SkeletalMeshComponent.h>
#include <GameFramework/Character.h>

void UNotifyState_Attack::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	ACharacter* pCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	if (pCharacter)
	{
		pCharacter->bUseControllerRotationYaw = false;
	}
}

void UNotifyState_Attack::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{

}

void UNotifyState_Attack::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ACharacter* pCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	if (pCharacter)
	{
		pCharacter->bUseControllerRotationYaw = true;
	}
}

