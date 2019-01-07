// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Manager_Item.generated.h"

/**
 * 
 */
class AItem_Base;


UCLASS()
class PROJECTA_API UManager_Item : public UObject
{
	GENERATED_BODY()

public :
	UManager_Item();
		
private :
	UPROPERTY()
	TArray<TSubclassOf<AItem_Base>> m_ItemClassList;

public :
	bool GetItemClassAt(uint16 _CodeNumber, TSubclassOf<AItem_Base>& _ItemClass) const;

private :
	UFUNCTION()
	bool _AddItemClassList(const TSubclassOf<AItem_Base>& _ItemClass, uint16 _CodeNumber);
	
};
