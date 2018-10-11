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

void UWidget_Equipment::InitWidget(UWidget_Main* _pMainWidget, UComponent_Base* _pComponent)
{
	UWidget_Base::InitWidget(_pMainWidget, _pComponent);

	UComponent_Equipment* pComp = Cast<UComponent_Equipment>(m_pComponent);

	m_pWeaponSlot->InitWidget(pComp, m_pMainWidget->GetDetailWidget());
	m_pWeaponSlot->SetSlotInfo(&pComp->GetWeaponSlot());

	m_pSecondaryWeaponSlot->InitWidget(pComp, m_pMainWidget->GetDetailWidget());
	m_pSecondaryWeaponSlot->SetSlotInfo(&pComp->GetSecondaryWeaponSlot());

	m_pNecklaceSlot->InitWidget(pComp, m_pMainWidget->GetDetailWidget());
	m_pNecklaceSlot->SetSlotInfo(&pComp->GetNecklaceSlot());

	m_pBeltSlot->InitWidget(pComp, m_pMainWidget->GetDetailWidget());
	m_pBeltSlot->SetSlotInfo(&pComp->GetBeltSlot());

	m_pRingSlot_L->InitWidget(pComp, m_pMainWidget->GetDetailWidget());
	m_pRingSlot_L->SetSlotInfo(&pComp->GetRingSlots()[0]);

	m_pRingSlot_R->InitWidget(pComp, m_pMainWidget->GetDetailWidget());
	m_pRingSlot_R->SetSlotInfo(&pComp->GetRingSlots()[1]);

	m_pEarringSlot_L->InitWidget(pComp, m_pMainWidget->GetDetailWidget());
	m_pEarringSlot_L->SetSlotInfo(&pComp->GetEarringSlots()[0]);

	m_pEarringSlot_R->InitWidget(pComp, m_pMainWidget->GetDetailWidget());
	m_pEarringSlot_R->SetSlotInfo(&pComp->GetEarringSlots()[1]);
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
	m_pComponent->Close();
}

