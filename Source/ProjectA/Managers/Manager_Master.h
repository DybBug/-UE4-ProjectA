// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Manager_Master.generated.h"

/**
 * 
 */
class UManager_AttackAnimMontages;

UCLASS()
class PROJECTA_API UManager_Master : public UGameInstance
{
	GENERATED_BODY()
	
public :
	UManager_Master();

protected :
	UPROPERTY()
	UManager_AttackAnimMontages* m_pAttackAnimMontagesManager;
	
	
};
