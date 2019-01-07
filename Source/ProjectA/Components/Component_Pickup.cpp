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

void UComponent_Pickup::InitComponent(UWidget_Base* _pWidget)
{
	UComponent_Base::InitComponent(_pWidget);
}

void UComponent_Pickup::Open()
{
	UWidget_Pickup* pWidget = Cast<UWidget_Pickup>(m_pWidget);
	pWidget->SetComponent(this);
	pWidget->GenerateSlots();

	UComponent_Base::Open();
}

void UComponent_Pickup::Close()
{
	UWidget_Pickup* pWidget = Cast<UWidget_Pickup>(m_pWidget);
	pWidget->RemoveSlots();

	UComponent_Base::Close();
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


void UComponent_Pickup::AddItemClass(const TSubclassOf<AItem_Base>& _ItemClass, int _Amount)
{
	m_Items.AddUnique(FPickupSlot_Info(_ItemClass, _Amount));
	m_PickupItemCount = m_Items.Num();
}

