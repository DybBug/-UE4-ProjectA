// Fill out your copyright notice in the Description page of Project Settings.

#include "NotifyState_WeaponAttack.h"
#include "Players/Player_Character.h"
#include "Items/Item_Equipment.h"
#include "Components/Component_Equipment.h"



void UNotifyState_WeaponAttack::NotifyBegin(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, float _TotalDuration)
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(_pMeshComp->GetOwner());
	if (pPlayer)
	{
		AItem_Equipment* pEquipment = pPlayer->GetEquipment()->GetWeaponSlot().pItem;
		pEquipment->StartAttack();
	}
}

void UNotifyState_WeaponAttack::NotifyEnd(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation)
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(_pMeshComp->GetOwner());
	if (pPlayer)
	{
		AItem_Equipment* pEquipment = pPlayer->GetEquipment()->GetWeaponSlot().pItem;
		pEquipment->EndAttack();
	}
}

