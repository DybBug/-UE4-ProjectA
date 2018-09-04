// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

public :
	UPROPERTY(EditAnywhere, Category = "Pickup_Info")
	TSubclassOf<AItem_Base> ItemClass;

	UPROPERTY(EditAnywhere, Category = "Pickup_Info")
	int Amount;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Pickup : public UActorComponent
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

	UWidget_Pickup* m_pPickupWidget;

	bool m_bIsOpen;

	int m_PickupItemCount;

public :
	void Open(UWidget_Pickup* _PickupWidget);
	void Close();

	const FPickupSlot_Info* GetItemInfoAtIndex(int _Index);

	int ItemCount();

	void RemoveItemAtIndex(int _Index, int _RemoveAmount);


	/* Get */
	FORCEINLINE const bool& GetIsOpen() const { return m_bIsOpen; }
};
