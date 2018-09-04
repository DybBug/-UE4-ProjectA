// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item_Base.h"
#include "Item_Compass.generated.h"

/**
 * 
 */
class UWidget_Compass;

UCLASS()
class PROJECTA_API AItem_Compass : public AItem_Base
{
	GENERATED_BODY()
	
protected :
	AItem_Compass();

protected :
	UWidget_Compass* m_pCompassWidget = nullptr;

	FTimerHandle m_hCompassTimer;

public :
	virtual void InitItem(AActor* _pOwner);
	virtual bool OnUse(FInventorySlot_Info* const pSlotInfo);

	void Open();
	void Close();

private :
	UFUNCTION()
	void _UpdateCompass();
	
};
