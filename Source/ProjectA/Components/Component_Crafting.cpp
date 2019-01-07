// Fill out your copyright notice in the Description page of Project Settings.

#include "Component_Crafting.h"
#include "Component_Inventory.h"
#include "Players/Player_Character.h"
#include "Widgets/Crafting/Widget_Crafting.h"
#include "Items/Item_Base.h"


// Sets default values for this component's properties
UComponent_Crafting::UComponent_Crafting()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UComponent_Crafting::BeginPlay()
{
	Super::BeginPlay();

}

void UComponent_Crafting::InitComponent(UWidget_Base* _pWidget)
{
	UComponent_Base::InitComponent(_pWidget);

	UWidget_Crafting* pWidget = Cast<UWidget_Crafting>(m_pWidget);
	pWidget->GenerateEntries();
}

void UComponent_Crafting::UpdateComponent()
{
	m_pWidget->UpdateWidget();
}

bool UComponent_Crafting::CreateItemAt(int _Index)
{
	AItem_Base* pItem = GetWorld()->SpawnActor<AItem_Base>(m_CraftingItems[_Index].CraftItemClass);
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	int Rest = pPlayer->GetInventory()->AddItem(pItem, 1);

	bool bSuccess = false;

	if (!Rest)
	{
		for (auto Recipe : m_CraftingItems[_Index].RecipeList)
		{
			TArray<int> SlotIndices = pPlayer->GetInventory()->GetSlotIndicesWithItem(Recipe.Key);

			for (auto SlotIndex : SlotIndices)
			{
				const FInventorySlot_Info& SlotInfo = pPlayer->GetInventory()->GetSlot(SlotIndex);
				if (SlotInfo.Amount >= Recipe.Value)
				{
					pPlayer->GetInventory()->ThrowAwayItem(SlotInfo.SlotIndex, Recipe.Value);
					UpdateComponent();
					break;
				}
				else
				{
					Recipe.Value -= SlotInfo.Amount;
					pPlayer->GetInventory()->ThrowAwayItem(SlotInfo.SlotIndex, SlotInfo.Amount);
					UpdateComponent();
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}


