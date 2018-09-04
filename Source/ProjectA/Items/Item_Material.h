// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item_Base.h"
#include "Item_Material.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API AItem_Material : public AItem_Base
{
	GENERATED_BODY()
	
public :
	virtual void InitItem(AActor* _pOwner) override {};
	virtual bool OnUse(FInventorySlot_Info* const pSlotInfo) override { return false; }
	
	
};
