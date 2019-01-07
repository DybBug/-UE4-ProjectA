// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Component_Base.h"
#include "Component_Pickup.generated.h"


class AItem_Base;
class UWidget_Pickup;

USTRUCT(BlueprintType)
struct FPickupSlot_Info
{
	GENERATED_BODY()

	FPickupSlot_Info()
		: ItemClass(nullptr), Amount(0) {};

	FPickupSlot_Info(TSubclassOf<AItem_Base> _pItemClass, int _Amount)
		: ItemClass(_pItemClass), Amount(_Amount) {}

	bool operator==(const FPickupSlot_Info& _rhs) const
	{
		return (this->ItemClass == _rhs.ItemClass) && (this->Amount == _rhs.Amount);
	}

public :
	UPROPERTY(EditAnywhere, Category = "Pickup_Info")
	TSubclassOf<AItem_Base> ItemClass;

	UPROPERTY(EditAnywhere, Category = "Pickup_Info")
	int Amount;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Pickup : public UComponent_Base
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Pickup();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TArray<FPickupSlot_Info> m_Items;

	int m_PickupItemCount;

public :
	virtual void InitComponent(UWidget_Base* _pWidget) override;

	virtual void Open() override;
	virtual void Close() override;

	const FPickupSlot_Info* GetItemInfoAtIndex(int _Index);

	int ItemCount();

	void RemoveItemAtIndex(int _Index, int _RemoveAmount);

	void AddItemClass(const TSubclassOf<AItem_Base>& _ItemClass, int _Amount);

};
