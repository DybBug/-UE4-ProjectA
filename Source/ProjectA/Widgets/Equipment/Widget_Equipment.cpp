// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Equipment.h"
#include "Widget_EquipmentSlot.h"
#include "Widgets/Widget_Main.h"
#include "Components/Component_Equipment.h"
#include "Operations/Operation_Slot.h"
#include "Items/Item_Equipment.h"

#include <Components/Button.h>

void UWidget_Equipment::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UWidget_Equipment::NativeConstruct()
{
	Super::NativeConstruct();

	m_pCloseButton->OnClicked.AddDynamic(this, &UWidget_Equipment::_OnCloseButtonClicked);
	
}

void UWidget_Equipment::InitWidget(UWidget_Main* _pMainWidget, UComponent_Equipment* _pEquipment)
{
	UWidget_Base::InitWidget(_pMainWidget);

	m_pEquipment = _pEquipment;

	m_pWeaponSlot->InitWidget(m_pEquipment, m_pMainWidget->GetDetailWidget());
	m_pWeaponSlot->SetSlotInfo(&m_pEquipment->GetWeaponSlot());

	m_pSecondaryWeaponSlot->InitWidget(m_pEquipment, m_pMainWidget->GetDetailWidget());
	m_pSecondaryWeaponSlot->SetSlotInfo(&m_pEquipment->GetSecondaryWeaponSlot());

	m_pNecklaceSlot->InitWidget(m_pEquipment, m_pMainWidget->GetDetailWidget());
	m_pNecklaceSlot->SetSlotInfo(&m_pEquipment->GetNecklaceSlot());

	m_pBeltSlot->InitWidget(m_pEquipment, m_pMainWidget->GetDetailWidget());
	m_pBeltSlot->SetSlotInfo(&m_pEquipment->GetBeltSlot());

	m_pRingSlot_L->InitWidget(m_pEquipment, m_pMainWidget->GetDetailWidget());
	m_pRingSlot_L->SetSlotInfo(&m_pEquipment->GetRingSlots()[0]);

	m_pRingSlot_R->InitWidget(m_pEquipment, m_pMainWidget->GetDetailWidget());
	m_pRingSlot_R->SetSlotInfo(&m_pEquipment->GetRingSlots()[1]);

	m_pEarringSlot_L->InitWidget(m_pEquipment, m_pMainWidget->GetDetailWidget());
	m_pEarringSlot_L->SetSlotInfo(&m_pEquipment->GetEarringSlots()[0]);

	m_pEarringSlot_R->InitWidget(m_pEquipment, m_pMainWidget->GetDetailWidget());
	m_pEarringSlot_R->SetSlotInfo(&m_pEquipment->GetEarringSlots()[1]);
}

bool UWidget_Equipment::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UOperation_Slot* pSlotOper = Cast<UOperation_Slot>(InOperation))
	{
		return true;
	}

	return false;
}


void UWidget_Equipment::_OnCloseButtonClicked()
{
	m_pEquipment->Close();
}

