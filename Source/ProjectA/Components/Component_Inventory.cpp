// Fill out your copyright notice in the Description page of Project Settings.

#include "Component_Inventory.h"
#include "Component_Crafting.h"
#include "Players/Player_Character.h"
#include "Items/Item_Base.h"
#include "Widgets/Inventory/Widget_Inventory.h"
#include "Widgets/Inventory/Widget_InventorySlot.h"

#define _DEBUG

// Sets default values for this component's properties
UComponent_Inventory::UComponent_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UComponent_Inventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


bool UComponent_Inventory::InitComponent(UWidget_Inventory* _pWidget)
{
	m_pInventoryWidget = _pWidget;
	_GenerateSlots();

	return true;
}

void UComponent_Inventory::Open()
{
	if (!m_bIsOpen)
	{
		m_bIsOpen = true;
		m_pInventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UComponent_Inventory::Close()
{
	if (m_bIsOpen)
	{
		m_bIsOpen = false;
		m_pInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

int UComponent_Inventory::AddItem(AItem_Base* _pNewItem, int _Amount)
{
	int Rest = _Amount;
	
	if (_pNewItem)
	{
		_pNewItem->InitItem(GetOwner());
		// #1. 적재 가능.
		if (_pNewItem->GetInfo().bCanStacked)
		{
			// #(1-1). 적재 가능한 슬롯 찾기.
			int SlotIndex = _SearchStackableSlotIndex(_pNewItem->GetClass());
			if (SlotIndex != -1)
			{
				int CurrAmountAtSlot = m_Slots[SlotIndex].Amount;

				if ((CurrAmountAtSlot + _Amount) > m_MaxStackCount)
				{
					m_Slots[SlotIndex].Amount = m_MaxStackCount;
					m_Slots[SlotIndex].pSlotWidget->UpdateWidget();

					_Amount = (CurrAmountAtSlot + _Amount) - m_MaxStackCount;

					Cast<APlayer_Character>(GetOwner())->GetCrafting()->UpdateComponent();

					return AddItem(_pNewItem, _Amount);
				}
				else
				{
					m_Slots[SlotIndex].Amount += _Amount;
					m_Slots[SlotIndex].pSlotWidget->UpdateWidget();
					_pNewItem->Destroy();

					Cast<APlayer_Character>(GetOwner())->GetCrafting()->UpdateComponent();
					return 0;
				}
			}
			else
			{
				// #(1-2). 빈슬롯 찾기.
				SlotIndex = _SearchEmptySlotIndex();
				if (SlotIndex != -1)
				{
					if (_Amount > m_MaxStackCount)
					{
						m_Slots[SlotIndex].pItem = _pNewItem;
						m_Slots[SlotIndex].Amount = m_MaxStackCount;
						m_Slots[SlotIndex].pSlotWidget->UpdateWidget();
					
						_pNewItem = GetWorld()->SpawnActor<AItem_Base>(_pNewItem->GetClass());
		
						Rest = _Amount - m_MaxStackCount;
						Cast<APlayer_Character>(GetOwner())->GetCrafting()->UpdateComponent();
						return AddItem(_pNewItem, Rest);
					}
					else
					{
						m_Slots[SlotIndex].pItem = _pNewItem;
						m_Slots[SlotIndex].Amount = _Amount;
						m_Slots[SlotIndex].pSlotWidget->UpdateWidget();
						Cast<APlayer_Character>(GetOwner())->GetCrafting()->UpdateComponent();
						return 0;
					}
				}
			}
		}

		// #2. 적재 불가능.
		else
		{
			int SlotIndex = _SearchEmptySlotIndex();
			if (SlotIndex != -1)
			{
				m_Slots[SlotIndex].pItem = _pNewItem;
				m_Slots[SlotIndex].Amount = 1;
				m_Slots[SlotIndex].pSlotWidget->UpdateWidget();
				Cast<APlayer_Character>(GetOwner())->GetCrafting()->UpdateComponent();
				_Amount--;
				if (_Amount >= 1)
				{
					_pNewItem = GetWorld()->SpawnActor<AItem_Base>(_pNewItem->GetClass());
		
					return AddItem(_pNewItem, _Amount);
				}
				else
				{
					return 0;
				}
			}
			else
			{
				Rest = _Amount;
				_pNewItem->Destroy();
				return Rest;
			}
		}
	}

	_pNewItem->Destroy();
	return Rest;
}

void UComponent_Inventory::MoveItem(const int& _ToSlotIndex, const int& _FromSlotIndex)
{
	m_Slots[_ToSlotIndex].Amount = m_Slots[_FromSlotIndex].Amount;
	m_Slots[_ToSlotIndex].pItem = m_Slots[_FromSlotIndex].pItem;

	m_Slots[_FromSlotIndex].Amount = 0;
	m_Slots[_FromSlotIndex].pItem = nullptr;

	m_Slots[_ToSlotIndex].pSlotWidget->UpdateWidget();
	m_Slots[_FromSlotIndex].pSlotWidget->UpdateWidget();
}

void UComponent_Inventory::CombineItem(const int& _ToSlotIndex, const int& _FromSlotIndex)
{
	if ((m_Slots[_ToSlotIndex].Amount + m_Slots[_FromSlotIndex].Amount) > m_MaxStackCount)
	{
		m_Slots[_FromSlotIndex].Amount = (m_Slots[_ToSlotIndex].Amount + m_Slots[_FromSlotIndex].Amount) - m_MaxStackCount;

		m_Slots[_ToSlotIndex].Amount = m_MaxStackCount;
	}
	else
	{
		m_Slots[_ToSlotIndex].Amount += m_Slots[_FromSlotIndex].Amount;

		m_Slots[_FromSlotIndex].Amount = 0;
		m_Slots[_FromSlotIndex].pItem->Destroy();
		m_Slots[_FromSlotIndex].pItem = nullptr;
	}
	
	m_Slots[_ToSlotIndex].pSlotWidget->UpdateWidget();
	m_Slots[_FromSlotIndex].pSlotWidget->UpdateWidget();
}

void UComponent_Inventory::SwapItem(const int& _ToSlotIndex, const int& _FromSlotIndex)
{
	int TempAmount = m_Slots[_ToSlotIndex].Amount;
	AItem_Base* pTempItem = m_Slots[_ToSlotIndex].pItem;
	
	m_Slots[_ToSlotIndex].Amount = m_Slots[_FromSlotIndex].Amount;
	m_Slots[_ToSlotIndex].pItem = m_Slots[_FromSlotIndex].pItem;

	m_Slots[_FromSlotIndex].Amount = TempAmount;
	m_Slots[_FromSlotIndex].pItem = pTempItem;

	m_Slots[_ToSlotIndex].pSlotWidget->UpdateWidget();
	m_Slots[_FromSlotIndex].pSlotWidget->UpdateWidget();
}

void UComponent_Inventory::ThrowAwayItem(const int& _SlotIndex, int _Amount)
{
	m_Slots[_SlotIndex].Amount -= _Amount;
	if (m_Slots[_SlotIndex].Amount <= 0)
	{
		m_Slots[_SlotIndex].Amount = 0;
		m_Slots[_SlotIndex].pItem->Destroy();
		m_Slots[_SlotIndex].pItem = nullptr;
	}
	m_Slots[_SlotIndex].pSlotWidget->UpdateWidget();
	Cast<APlayer_Character>(GetOwner())->GetCrafting()->UpdateComponent();

}

int UComponent_Inventory::GetAmountItem(TSubclassOf<AItem_Base> _ItemClass)
{
	int Amount = 0;
	for (auto Slot : m_Slots)
	{
		if (Slot.pItem && (Slot.pItem->GetClass() == _ItemClass))
		{
			Amount += Slot.Amount;
		}
	}
	return Amount;
}

TArray<int> UComponent_Inventory::GetSlotIndicesWithItem(TSubclassOf<AItem_Base> _ItemClass)
{
	TArray<int> SlotIndeices;

	for (int i = 0; i < m_Slots.Num(); ++i)
	{
		if (m_Slots[i].pItem && m_Slots[i].pItem->GetClass() == _ItemClass)
		{
			SlotIndeices.Add(i);
		}
	}
	return SlotIndeices;
}

const FInventorySlot_Info& UComponent_Inventory::GetSlot(int _Index) const
{
	//if (m_Slots.IsValidIndex(_Index))
	{
		return m_Slots[_Index];
	}
}

void UComponent_Inventory::_GenerateSlots()
{
	m_Slots.Empty();
	m_Slots.SetNum(m_SlotTotalCount);
	if (m_pInventoryWidget)
	{
		for (int i = 0; i < m_Slots.Num(); ++i)
		{
			int Row = (i / m_SlotsPerRow);
			int Column = (i % m_SlotsPerRow);

			m_Slots[i].SlotIndex = i;

			m_pInventoryWidget->GenerateSlots(&m_Slots[i], Row, Column);
		}
	}
}

int UComponent_Inventory::_SearchEmptySlotIndex()
{
	for (int i = 0; i < m_Slots.Num(); ++i)
	{
		if (!m_Slots[i].pItem)
		{
			return i;
		}
	}

	return -1;
}

int UComponent_Inventory::_SearchStackableSlotIndex(TSubclassOf<AItem_Base> _ItemClass)
{
	for (int i = 0; i < m_Slots.Num(); ++i)
	{
		if (m_Slots[i].pItem && (m_Slots[i].pItem->GetClass() == _ItemClass))
		{
			if (m_Slots[i].Amount < m_MaxStackCount)
			{
				return i;
			}
		}
	}

	return -1;
}


