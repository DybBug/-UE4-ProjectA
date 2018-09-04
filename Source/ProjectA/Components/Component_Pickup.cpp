// Fill out your copyright notice in the Description page of Project Settings.

#include "Component_Pickup.h"
#include "Widgets/Pickup/Widget_Pickup.h"
#include "Interfaces/Interface_Interaction.h"


// Sets default values for this component's properties
UComponent_Pickup::UComponent_Pickup()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	m_PickupItemCount = 0;
}


// Called when the game starts
void UComponent_Pickup::BeginPlay()
{
	Super::BeginPlay();	

	m_PickupItemCount = m_Items.Num();
}

void UComponent_Pickup::Open(UWidget_Pickup* _PickupWidget)
{
	m_bIsOpen = true;
	m_pPickupWidget = _PickupWidget;

	m_pPickupWidget->Show(this);
}

void UComponent_Pickup::Close()
{
	m_bIsOpen = false;
	m_pPickupWidget->Hide();

	m_pPickupWidget = nullptr;
}

const FPickupSlot_Info* UComponent_Pickup::GetItemInfoAtIndex(int _Index)
{
	if (!m_Items.IsValidIndex(_Index))
	{
		return nullptr;
	}

	return &m_Items[_Index];
}

int UComponent_Pickup::ItemCount()
{
	return m_Items.Num();
}

void UComponent_Pickup::RemoveItemAtIndex(int _Index, int _RemoveAmount)
{
	if (m_Items.IsValidIndex(_Index) && (m_Items[_Index].Amount > 0))
	{
		m_Items[_Index].Amount -= _RemoveAmount;

		if (m_Items[_Index].Amount == 0)
		{
			m_Items[_Index].ItemClass = nullptr;
			m_PickupItemCount--;

			if (m_PickupItemCount == 0)
			{
				Cast<IInterface_Interaction>(GetOwner())->UnInteract();
				GetOwner()->Destroy();
			}
		}
	}
	
	return;
}

