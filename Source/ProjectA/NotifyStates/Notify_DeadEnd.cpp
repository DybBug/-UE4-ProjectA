// Fill out your copyright notice in the Description page of Project Settings.

#include "Notify_DeadEnd.h"
#include "Enemies/Enemy_Base.h"

#include <Components/SkeletalMeshComponent.h>


void UNotify_DeadEnd::Notify(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation)
{
	_pMeshComp->GetOwner()->SetActorHiddenInGame(true);
}
