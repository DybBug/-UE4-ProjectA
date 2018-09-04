// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Manager_AttackAnimMontages.generated.h"

/**
 * 
 */
class UAnimMontage;

UCLASS()
class PROJECTA_API UManager_AttackAnimMontages : public UObject
{
	GENERATED_BODY()

public :
	UManager_AttackAnimMontages();
	
protected :
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TMap<FName, UAnimMontage*> m_AnimMontages;

public :
	FORCEINLINE const UAnimMontage* const& GetAnimMontageByName(FName _Name) const { return m_AnimMontages[_Name]; }


private :
	void _ObjectFindFail(TCHAR* _Text);
	
	
};
