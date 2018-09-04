// Fill out your copyright notice in the Description page of Project Settings.

#include "Component_Equipment.h"
#include "Component_Inventory.h"
#include "Items/Item_Equipment.h"
#include "Players/Player_Character.h"
#include "Widgets/Equipment/Widget_Equipment.h"
#include "Widgets/Equipment/Widget_EquipmentSlot.h"

#include <Components/SkeletalMeshComponent.h>
#include <Engine.h>


// Sets default values for this component's properties
UComponent_Equipment::UComponent_Equipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	m_EarringSlots.SetNum(2);
	m_RingSlots.SetNum(2);

	m_RingIndex = 0;
	m_EarringIndex = 0;
}


// Called when the game starts
void UComponent_Equipment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UComponent_Equipment::InitComponent(UWidget_Equipment* _pWidget)
{
	m_pEquipmentWidget = _pWidget;

	m_WeaponSlot.pSlotWidget = m_pEquipmentWidget->GetWeaponSlot();
	m_WeaponSlot.pSlotWidget->BindEquipFunc(this, &UComponent_Equipment::_EquipWeapon);
	m_WeaponSlot.pSlotWidget->BindUnEquipFunc(this, &UComponent_Equipment::_UnEquipWeapon);

	m_SecondaryWeaponSlot.pSlotWidget = m_pEquipmentWidget->GetSecondaryWeaponSlot();
	m_SecondaryWeaponSlot.pSlotWidget->BindEquipFunc(this, &UComponent_Equipment::_EquipSecondaryWeapon);
	m_SecondaryWeaponSlot.pSlotWidget->BindUnEquipFunc(this, &UComponent_Equipment::_UnEquipSecondaryWeapon);

	m_NecklaceSlot.pSlotWidget = m_pEquipmentWidget->GetNecklaceSlot();
	m_NecklaceSlot.pSlotWidget->BindEquipFunc(this, &UComponent_Equipment::_EquipNecklace);
	m_NecklaceSlot.pSlotWidget->BindUnEquipFunc(this, &UComponent_Equipment::_UnEquipNecklace);

	m_BeltSlot.pSlotWidget = m_pEquipmentWidget->GetBeltSlot();
	m_BeltSlot.pSlotWidget->BindEquipFunc(this, &UComponent_Equipment::_EquipBelt);
	m_BeltSlot.pSlotWidget->BindUnEquipFunc(this, &UComponent_Equipment::_UnEquipBelt);

	m_RingSlots[0].pSlotWidget = m_pEquipmentWidget->GetRingSlot_L();
	m_RingSlots[0].pSlotWidget->BindEquipFunc(this, &UComponent_Equipment::_EquipRing_L);
	m_RingSlots[0].pSlotWidget->BindUnEquipFunc(this, &UComponent_Equipment::_UnEquipRing_L);

	m_RingSlots[1].pSlotWidget = m_pEquipmentWidget->GetRingSlot_R();
	m_RingSlots[1].pSlotWidget->BindEquipFunc(this, &UComponent_Equipment::_EquipRing_R);
	m_RingSlots[1].pSlotWidget->BindUnEquipFunc(this, &UComponent_Equipment::_UnEquipRing_R);

	m_EarringSlots[0].pSlotWidget = m_pEquipmentWidget->GetEarringSlot_L();
	m_EarringSlots[0].pSlotWidget->BindEquipFunc(this, &UComponent_Equipment::_EquipEarring_L);
	m_EarringSlots[0].pSlotWidget->BindUnEquipFunc(this, &UComponent_Equipment::_UnEquipEarring_L);

	m_EarringSlots[1].pSlotWidget = m_pEquipmentWidget->GetEarringSlot_R();
	m_EarringSlots[1].pSlotWidget->BindEquipFunc(this, &UComponent_Equipment::_EquipEarring_R);
	m_EarringSlots[1].pSlotWidget->BindUnEquipFunc(this, &UComponent_Equipment::_UnEquipEarring_R);
}

void UComponent_Equipment::Open()
{
	m_bIsOpen = true;
	m_pEquipmentWidget->SetVisibility(ESlateVisibility::Visible);
}

void UComponent_Equipment::Close()
{
	m_bIsOpen = false;
	m_pEquipmentWidget->SetVisibility(ESlateVisibility::Hidden);
}

bool UComponent_Equipment::OnEquip(AItem_Equipment* _pEquipment)
{
	EEquipment_Types EquipmentType = _pEquipment->GetEquipmentType();

	switch (EquipmentType)
	{
		case EEquipment_Types::Weapon :
		{
			return _EquipWeapon(_pEquipment);
		}
		case EEquipment_Types::SecondaryWeapon :
		{
			return _EquipSecondaryWeapon(_pEquipment);
		}
		case EEquipment_Types::Necklace :
		{
			return _EquipNecklace(_pEquipment);
		}
		case EEquipment_Types::Belt :
		{
			return _EquipBelt(_pEquipment);
		}
		case EEquipment_Types::Ring :
		{
			return _EquipRing(_pEquipment);
		}
		case EEquipment_Types::Earring :
		{
			return _EquipEarring(_pEquipment);
		}
		default :
		{
			break;
		}
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////
// #. 장비 장착.
//
bool UComponent_Equipment::_EquipWeapon(AItem_Equipment* _pEquipment)
{
	_UnEquipWeapon();

	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());

	FName WeaponSocketName = _pEquipment->GetSocketName();
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	_pEquipment->AttachToComponent(pPlayer->GetMesh(), TransformRules, WeaponSocketName);
	_pEquipment->SetActorHiddenInGame(false);

	m_WeaponSlot.pItem = _pEquipment;
	m_WeaponSlot.pSlotWidget->Show();
	_UpdatePlayerStats(m_WeaponSlot.pItem, true);

	return true;
}

bool UComponent_Equipment::_EquipSecondaryWeapon(AItem_Equipment* _pEquipment)
{
	_UnEquipSecondaryWeapon();

	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());

	FName WeaponSocketName = _pEquipment->GetSocketName();
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	_pEquipment->AttachToComponent(pPlayer->GetMesh(), TransformRules, WeaponSocketName);
	_pEquipment->SetActorHiddenInGame(false);

	m_SecondaryWeaponSlot.pItem = _pEquipment;
	m_SecondaryWeaponSlot.pSlotWidget->Show();
	_UpdatePlayerStats(m_SecondaryWeaponSlot.pItem, true);

	return true;
}

bool UComponent_Equipment::_EquipNecklace(AItem_Equipment* _pEquipment)
{
	_UnEquipNecklace();

	m_NecklaceSlot.pItem = _pEquipment;
	m_NecklaceSlot.pSlotWidget->Show();
	_UpdatePlayerStats(m_NecklaceSlot.pItem, true);
	return true;
}

bool UComponent_Equipment::_EquipBelt(AItem_Equipment* _pEquipment)
{
	_UnEquipBelt();

	m_BeltSlot.pItem = _pEquipment;
	m_BeltSlot.pSlotWidget->Show();
	_UpdatePlayerStats(m_BeltSlot.pItem, true);
	return true;
}

bool UComponent_Equipment::_EquipRing(AItem_Equipment* _pEquipment)
{	
	_UnEquipRing();

	if (m_RingIndex == 0)
	{
		_EquipRing_L(_pEquipment);
	}
	else
	{
		_EquipRing_R(_pEquipment);
	}

	m_RingIndex = ((m_RingIndex + 1) % 2);
	return true;
}

bool UComponent_Equipment::_EquipEarring(AItem_Equipment* _pEquipment)
{
	_UnEquipEarring();

	if (m_RingIndex == 0)
	{
		_EquipEarring_L(_pEquipment);
	}
	else
	{
		_EquipEarring_R(_pEquipment);
	}

	m_EarringIndex = ((m_EarringIndex + 1) % 2);
	return true;
}

/////////////////////////////////////////////////////////////////////////
// #. 장비 해제.
//

bool UComponent_Equipment::_UnEquipWeapon()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	if (pPlayer)
	{
		if (m_WeaponSlot.pItem)
		{
			int Rest = pPlayer->GetInventory()->AddItem(m_WeaponSlot.pItem, 1);
			if (Rest == 0)
			{
				_UpdatePlayerStats(m_WeaponSlot.pItem, false);
				FDetachmentTransformRules Param(EDetachmentRule::KeepWorld, false);
				m_WeaponSlot.pItem->DetachFromActor(Param);
				m_WeaponSlot.pItem->SetActorHiddenInGame(true);
				m_WeaponSlot.pItem = nullptr;
				m_WeaponSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UComponent_Equipment::_UnEquipSecondaryWeapon()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	if (pPlayer)
	{
		if (m_SecondaryWeaponSlot.pItem)
		{
			int Rest = pPlayer->GetInventory()->AddItem(m_SecondaryWeaponSlot.pItem, 1);
			if (Rest == 0)
			{
				_UpdatePlayerStats(m_SecondaryWeaponSlot.pItem, false);
				FDetachmentTransformRules Param(EDetachmentRule::KeepRelative, false);
				m_SecondaryWeaponSlot.pItem->DetachFromActor(Param);
				m_SecondaryWeaponSlot.pItem->SetActorHiddenInGame(true);
				m_SecondaryWeaponSlot.pItem = nullptr;
				m_SecondaryWeaponSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UComponent_Equipment::_UnEquipNecklace()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	if (pPlayer)
	{
		if (m_NecklaceSlot.pItem)
		{
			int Rest = pPlayer->GetInventory()->AddItem(m_NecklaceSlot.pItem, 1);
			if (Rest == 0)
			{
				_UpdatePlayerStats(m_NecklaceSlot.pItem, false);
				m_NecklaceSlot.pItem = nullptr;
				m_NecklaceSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UComponent_Equipment::_UnEquipBelt()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	if (pPlayer)
	{
		if (m_BeltSlot.pItem)
		{
			int Rest = pPlayer->GetInventory()->AddItem(m_BeltSlot.pItem, 1);
			if (Rest == 0)
			{
				_UpdatePlayerStats(m_BeltSlot.pItem, false);
				m_BeltSlot.pItem = nullptr;
				m_BeltSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UComponent_Equipment::_UnEquipRing()
{
	if (m_RingIndex == 0)
	{
		return _UnEquipRing_L();
	}
	else
	{
		return _UnEquipRing_R();
	}
	return false;
}

bool UComponent_Equipment::_UnEquipEarring()
{
	if (m_EarringIndex == 0)
	{
		return _UnEquipEarring_L();
	}
	else
	{
		return _UnEquipEarring_R();
	}
	return false;
}

///////////////////////////////////////////////////////////////////
// #. 귀걸이, 반지 왼쪽, 오른쪽 장착 및 해제.
//

bool UComponent_Equipment::_EquipRing_L(AItem_Equipment* _pEquipment)
{
	m_RingSlots[0].pItem = _pEquipment;
	m_RingSlots[0].pSlotWidget->Show();
	_UpdatePlayerStats(m_RingSlots[0].pItem, true);
	return true;
}

bool UComponent_Equipment::_UnEquipRing_L()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	if (pPlayer)
	{
		if (m_RingSlots[0].pItem)
		{
			int Rest = pPlayer->GetInventory()->AddItem(m_RingSlots[0].pItem, 1);
			if (Rest == 0)
			{
				_UpdatePlayerStats(m_RingSlots[0].pItem, false);
				m_RingSlots[0].pItem = nullptr;
				m_RingSlots[0].pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UComponent_Equipment::_EquipRing_R(AItem_Equipment* _pEquipment)
{
	m_RingSlots[1].pItem = _pEquipment;
	m_RingSlots[1].pSlotWidget->Show();
	_UpdatePlayerStats(m_RingSlots[1].pItem, true);
	return true;
}

bool UComponent_Equipment::_UnEquipRing_R()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	if (pPlayer)
	{
		if (m_RingSlots[1].pItem)
		{
			int Rest = pPlayer->GetInventory()->AddItem(m_RingSlots[1].pItem, 1);
			if (Rest == 0)
			{
				_UpdatePlayerStats(m_RingSlots[1].pItem, false);
				m_RingSlots[1].pItem = nullptr;
				m_RingSlots[1].pSlotWidget->Hide();

				return true;
			}
		}
	}
	return false;
}


bool UComponent_Equipment::_EquipEarring_L(AItem_Equipment* _pEquipment)
{
	m_EarringSlots[0].pItem = _pEquipment;
	m_EarringSlots[0].pSlotWidget->Show();
	_UpdatePlayerStats(m_EarringSlots[0].pItem, true);
	return true;
}

bool UComponent_Equipment::_UnEquipEarring_L()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	if (pPlayer)
	{
		if (m_EarringSlots[0].pItem)
		{
			int Rest = pPlayer->GetInventory()->AddItem(m_EarringSlots[0].pItem, 1);
			if (Rest == 0)
			{
				_UpdatePlayerStats(m_EarringSlots[0].pItem, false);
				m_EarringSlots[0].pItem = nullptr;
				m_EarringSlots[0].pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UComponent_Equipment::_EquipEarring_R(AItem_Equipment* _pEquipment)
{	
	_UpdatePlayerStats(m_EarringSlots[1].pItem, true);
	m_EarringSlots[1].pItem = _pEquipment;
	m_EarringSlots[1].pSlotWidget->Show();
	return true;
}

bool UComponent_Equipment::_UnEquipEarring_R()
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());
	if (pPlayer)
	{
		if (m_EarringSlots[1].pItem)
		{
			int Rest = pPlayer->GetInventory()->AddItem(m_EarringSlots[1].pItem, 1);
			if (Rest == 0)
			{
				_UpdatePlayerStats(m_EarringSlots[1].pItem, false);
				m_EarringSlots[1].pItem = nullptr;
				m_EarringSlots[1].pSlotWidget->Hide();			
				return true;
			}
		}
	}
	return false;
}

void UComponent_Equipment::_UpdatePlayerStats(AItem_Equipment* _pEquipment, bool _bIsPositive)
{
	APlayer_Character* pPlayer = Cast<APlayer_Character>(GetOwner());

	FItem_Info ItemInfo = _pEquipment->GetInfo();

	int Sign = _bIsPositive ? 1 : -1;

	for (auto ItemAbility : ItemInfo.AbilityList)
	{
		pPlayer->ModifyStat(ItemAbility.Key, Sign * ItemAbility.Value);
	}
}


