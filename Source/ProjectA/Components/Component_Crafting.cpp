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
	m_bIsOpen = false;
}

// Called when the game starts
void UComponent_Crafting::BeginPlay()
{
	Super::BeginPlay();

}

void UComponent_Crafting::InitComponent(UWidget_Crafting* _pWidget)
{
	m_pCraftingWidget = _pWidget;
	m_pCraftingWidget->GenerateEntries();
}

void UComponent_Crafting::UpdateComponent()
{
	m_pCraftingWidget->UpdateWidget();
}

bool UComponent_Crafting::CreateItem(const FCrafting_Info& _Crafting_Info)
{
	AItem_Base* pItem = GetWorld()->SpawnActor<AItem_Base>(_Crafting_Info.CraftItemClass);
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	int Rest = pPlayer->GetInventory()->AddItem(pItem, 1);

	bool bSuccess = false;

	if (!Rest)
	{
		for (auto Recipe : _Crafting_Info.RecipeList)
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

void UComponent_Crafting::Open()
{
	if (!m_bIsOpen)
	{
		m_bIsOpen = true;
		m_pCraftingWidget->Show();
	}
}

void UComponent_Crafting::Close()
{
	if (m_bIsOpen)
	{
		m_bIsOpen = false;
		m_pCraftingWidget->Hide();
	}
}

