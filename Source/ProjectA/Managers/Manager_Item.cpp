// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager_Item.h"
#include "Items/Item_Base.h"

#include <UObject/ConstructorHelpers.h>

UManager_Item::UManager_Item()
{
	// #. Consumables.
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_ExpBook(TEXT("Blueprint'/Game/01_Blueprints/Items/Consumables/BP_ExpBook.BP_ExpBook_C'"));
	if (!_AddItemClassList(BP_ExpBook.Class, 0))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_ExpBook.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_HealthPotion(TEXT("Blueprint'/Game/01_Blueprints/Items/Consumables/BP_HealthPotion.BP_HealthPotion_C'"));
	if (!_AddItemClassList(BP_HealthPotion.Class, 1))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_HealthPotion.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_ManaPotion(TEXT("Blueprint'/Game/01_Blueprints/Items/Consumables/BP_ManaPotion.BP_ManaPotion_C'"));
	if (!_AddItemClassList(BP_ManaPotion.Class, 2))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_ManaPotion.GetReferencerName());
	}

	// #. Equipments.
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Axe(TEXT("Blueprint'/Game/01_Blueprints/Items/Equipments/BP_Axe.BP_Axe_C'"));
	if (!_AddItemClassList(BP_Axe.Class, 3))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Axe.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Belt(TEXT("Blueprint'/Game/01_Blueprints/Items/Equipments/BP_Belt.BP_Belt_C'"));
	if (!_AddItemClassList(BP_Belt.Class, 4))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Belt.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Earring(TEXT("Blueprint'/Game/01_Blueprints/Items/Equipments/BP_Earring.BP_Earring_C'"));
	if (!_AddItemClassList(BP_Earring.Class, 5))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Earring.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Necklace(TEXT("Blueprint'/Game/01_Blueprints/Items/Equipments/BP_Necklace.BP_Necklace_C'"));
	if (!_AddItemClassList(BP_Necklace.Class, 6))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Necklace.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Ring(TEXT("Blueprint'/Game/01_Blueprints/Items/Equipments/BP_Ring.BP_Ring_C'"));
	if (!_AddItemClassList(BP_Ring.Class, 7))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Ring.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Shield(TEXT("Blueprint'/Game/01_Blueprints/Items/Equipments/BP_Shield.BP_Shield_C'"));
	if (!_AddItemClassList(BP_Shield.Class, 8))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Shield.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Sword(TEXT("	Blueprint'/Game/01_Blueprints/Items/Equipments/BP_Sword.BP_Sword_C'"));
	if (!_AddItemClassList(BP_Sword.Class, 9))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Sword.GetReferencerName());
	}

	// #. Materials.
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_BlueStone(TEXT("Blueprint'/Game/01_Blueprints/Items/Materials/BP_BlueStone.BP_BlueStone_C'"));
	if (!_AddItemClassList(BP_BlueStone.Class, 10))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_BlueStone.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Bottle(TEXT("Blueprint'/Game/01_Blueprints/Items/Materials/BP_Bottle.BP_Bottle_C'"));
	if (!_AddItemClassList(BP_Bottle.Class, 11))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Bottle.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_RedStone(TEXT("Blueprint'/Game/01_Blueprints/Items/Materials/BP_RedStone.BP_RedStone_C'"));
	if (!_AddItemClassList(BP_RedStone.Class, 12))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_RedStone.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Stone(TEXT("Blueprint'/Game/01_Blueprints/Items/Materials/BP_Stone.BP_Stone_C'"));
	if (!_AddItemClassList(BP_Stone.Class, 13))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Stone.GetReferencerName());
	}
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Wood(TEXT("Blueprint'/Game/01_Blueprints/Items/Materials/BP_Wood.BP_Wood_C'"));
	if (!_AddItemClassList(BP_Wood.Class, 14))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Wood.GetReferencerName());
	}

	// #. Misc.
	static ConstructorHelpers::FClassFinder<AItem_Base> BP_Compass(TEXT("Blueprint'/Game/01_Blueprints/Items/Misc/BP_Compass.BP_Compass_C'"));
	if (!_AddItemClassList(BP_Compass.Class, 15))
	{
		UE_LOG(LogClass, Warning, TEXT("%s Load Failed!"), *BP_Compass.GetReferencerName());
	}
}

bool UManager_Item::GetItemClassAt(uint16 _CodeNumber, TSubclassOf<AItem_Base>& _ItemClass) const
{
	if (m_ItemClassList.IsValidIndex(_CodeNumber))
	{
		_ItemClass = m_ItemClassList[_CodeNumber];
		return true;
	}

	_ItemClass = nullptr;
	return false;
}


bool UManager_Item::_AddItemClassList(const TSubclassOf<AItem_Base>& _ItemClass, uint16 _CodeNumber)
{
	if (_ItemClass.Get())
	{
		m_ItemClassList.Add(_ItemClass);
		m_ItemClassList.Last().GetDefaultObject()->SetCodeNumber(_CodeNumber);
		return true;
	}
	else
	{
		return false;
	}
}