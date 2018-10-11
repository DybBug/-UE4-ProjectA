// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Component_Base.h"
#include "Component_Inventory.generated.h"


class UWidget_InventorySlot;
class AItem_Base;

USTRUCT(BlueprintType)
struct FInventorySlot_Info
{
	GENERATED_BODY()

	FInventorySlot_Info() 
		: SlotIndex(0), pSlotWidget(nullptr), pItem(nullptr), Amount(0) {};

	FInventorySlot_Info(int _SlotIndex, UWidget_InventorySlot* _pSlotWidget, AItem_Base* _pNewItem, int _NewAmount)
		: SlotIndex(_SlotIndex), pSlotWidget(_pSlotWidget), pItem(_pNewItem), Amount(_NewAmount){};

public:
	UPROPERTY(VisibleAnywhere, Category = "InventorySlot_Info")
	int SlotIndex;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlot_Info")
	UWidget_InventorySlot* pSlotWidget;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlot_Info")
	AItem_Base * pItem;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlot_Info")
	int Amount;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Inventory : public UComponent_Base
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Inventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private :
	// #. �� ���Կ� ���� ������ �ִ� ����.
	UPROPERTY(EditDefaultsOnly, Category = "Configuration")
	int m_MaxStackCount;

	// #. �κ��丮 ������ �� ����.
	UPROPERTY(EditDefaultsOnly, Category = "Configuration")
	int m_SlotTotalCount;

	// #. �� �� ���� ��.
	UPROPERTY(EditDefaultsOnly, Category = "Configuration")
	int m_SlotsPerRow;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TArray<FInventorySlot_Info> m_Slots;

public :
	virtual void InitComponent(UWidget_Base* _pWidget) override;
	virtual void UpdateComponent() override;

	// #. Return : �߰��ϰ� ���� ����.
	int AddItem(AItem_Base* _pNewItem, int _Amount);

	// #. ������ �̵�.
	void MoveItem(const int& _ToSlotIndex, const int& _FromSlotIndex);

	// #. ������ ��ġ��.
	void CombineItem(const int& _ToSlotIndex, const int& _FromSlotIndex);

	// #. ������ ��ü.
	void SwapItem(const int& _ToSlotIndex, const int& _FromSlotIndex);

	void ThrowAwayItem(const int& _SlotIndex, int _Amount);

	// #. �ش� �������� �κ��丮�� �ִ� �� ����.
	int GetAmountItem(TSubclassOf<AItem_Base> _ItemClass);

	// #. �ش� �������� �ִ� ���Ե��� �ε�����.
	TArray<int> GetSlotIndicesWithItem(TSubclassOf<AItem_Base> _ItemClass);

	FORCEINLINE const FInventorySlot_Info& GetSlot(int _Index) const;

	/* Get */
	FORCEINLINE const int&  GetMaxStackCount()  const { return m_MaxStackCount; }
	FORCEINLINE const int&  GetSlotTotalCount() const { return m_SlotTotalCount; }
	FORCEINLINE const int&  GetSlotsPerRow()    const { return m_SlotsPerRow; }
	FORCEINLINE const bool& GetIsOpen()         const { return m_bIsOpen; }

	FORCEINLINE const TArray<FInventorySlot_Info>& GetSlots() const { return m_Slots; }

	/* Set */
	FORCEINLINE void SetSlot(const FInventorySlot_Info& _Slot) { m_Slots.Emplace(_Slot); }

private :
	void _GenerateSlots();

	// #. �󽽷� �ε��� ã��.
	// #. �����ϸ� -1�� ��ȯ.
	int _SearchEmptySlotIndex();

	// #. ���� ������ ���� ã��.
	// #. �����ϸ� -1�� ��ȯ.
	int _SearchStackableSlotIndex(TSubclassOf<AItem_Base> _ItemClass);

};
