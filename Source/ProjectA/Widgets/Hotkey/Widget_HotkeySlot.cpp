// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_HotkeySlot.h"
#include "Widget_Hotkey.h"
#include "Widgets/Inventory/Widget_InventorySlot.h"
#include "Widgets/SkillTree/Widget_SkillEntry.h"
#include "Skills/Skill_Buff.h"
#include "Items/Item_Base.h"
#include "Components/Component_Inventory.h"
#include "Operations/Operation_Slot.h"

#include <Components/TextBlock.h>
#include <Components/Border.h>
#include <Components/Image.h>
#include <Materials/MaterialInstanceDynamic.h>

#define LOCTEXT_NAMESPACE "Format"

void UWidget_HotkeySlot::NativePreConstruct()
{
	FText Format = FText::Format(LOCTEXT("Format", "[{0}]"), m_Hotkey.GetDisplayName());

	m_pHotkeyText->SetText(Format);
	m_DefaultColor = m_pOutline->BrushColor;
}

void UWidget_HotkeySlot::NativeConstruct()
{
	m_pNum->SetVisibility(ESlateVisibility::Hidden);
	m_pCooldownImage->SetVisibility(ESlateVisibility::Hidden);
	m_pCooldownText->SetVisibility(ESlateVisibility::Hidden);

	m_pDynamicMaterial = m_pCooldownImage->GetDynamicMaterial();
}

void UWidget_HotkeySlot::InitWidget(UWidget_Hotkey* _pWidget, const FKey& _Key, int _Index)
{
	m_pHotkeyWidget = _pWidget;
	m_Hotkey = _Key;
	m_Index = _Index;
}

void UWidget_HotkeySlot::UpdateWidget()
{
	if (m_pAssignedWidget)
	{
		if (UWidget_InventorySlot* pInventorySlot = Cast<UWidget_InventorySlot>(m_pAssignedWidget))
		{
			if (pInventorySlot->GetSlotInfo()->pItem)
			{
				m_pIcon->SetVisibility(ESlateVisibility::Visible);
				m_pIcon->SetBrushFromTexture(pInventorySlot->GetSlotInfo()->pItem->GetInfo().pIcon);

				int Amount = pInventorySlot->GetSlotInfo()->Amount;
				if (Amount > 1)
				{
					m_pNum->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					m_pNum->SetText(FText::AsNumber(Amount));
				}
				else
				{
					m_pNum->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			else
			{
				m_pAssignedWidget = nullptr;
				UpdateWidget();
			}
		}
		else if (UWidget_SkillEntry* pSkillEntry = Cast<UWidget_SkillEntry>(m_pAssignedWidget))
		{
			ASkill_Buff* pSkill = Cast<ASkill_Buff>(pSkillEntry->GetSkill());
			if (pSkill)
			{
				m_pIcon->SetVisibility(ESlateVisibility::Visible);
				m_pIcon->SetBrushFromTexture(pSkill->GetInfo().pIcon);

				m_pNum->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				m_pNum->SetText(FText::AsNumber(pSkill->GetInfo().CurrentLevel));
			}
		}
	}
	else
	{
		m_pIcon->SetBrushFromTexture(nullptr);
		m_pIcon->SetVisibility(ESlateVisibility::Hidden);
		m_pNum->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_HotkeySlot::Use()
{
	if (m_pAssignedWidget)
	{
		if (UWidget_InventorySlot* pInventorySlot = Cast<UWidget_InventorySlot>(m_pAssignedWidget))
		{
			AItem_Base* pItem = pInventorySlot->GetSlotInfo()->pItem;
			if (pItem)
			{
				if (pItem->OnUse(pInventorySlot->GetSlotInfo()))
				{
					pInventorySlot->UpdateWidget();
					UpdateWidget();
				}
			}
		}
		else if (UWidget_SkillEntry* pSkillEntry = Cast<UWidget_SkillEntry>(m_pAssignedWidget))
		{
			ASkill_Base* pSkill = pSkillEntry->GetSkill();
			if (pSkill)
			{
				pSkill->Use();
			}
		}
	}
}

void UWidget_HotkeySlot::UpdateCooldown(float _Percent)
{
	m_pDynamicMaterial->SetScalarParameterValue("Percent", _Percent);
}

void UWidget_HotkeySlot::ActivateCooldown()
{
	m_pIcon->SetColorAndOpacity(FLinearColor(FColor(0x545454FF)));
	m_pCooldownImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWidget_HotkeySlot::DetactiveCooldown()
{
	m_pIcon->SetColorAndOpacity(FLinearColor(FColor(0xFFFFFFFF)));
	m_pCooldownImage->SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_HotkeySlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UOperation_Slot* pOperSlot = Cast<UOperation_Slot>(InOperation))
	{
		if (UWidget_InventorySlot* pInventorySlot = Cast<UWidget_InventorySlot>(pOperSlot->GetDraggedSlot()))
		{
			if (pInventorySlot->GetSlotInfo()->pItem->GetInfo().bCanUsed)
			{
				m_pOutline->SetBrushColor(FColor::Green);
			}

		}
		else if (UWidget_SkillEntry* pSkillEntry = Cast<UWidget_SkillEntry>(pOperSlot->GetDraggedSlot()))
		{
			if (ASkill_Buff* pSkill = Cast<ASkill_Buff>(pSkillEntry->GetSkill()))
			{
				m_pOutline->SetBrushColor(FColor::Green);
			}
		}
		else
		{
			m_pOutline->SetBrushColor(FColor::Red);
		}
	}
}

void UWidget_HotkeySlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	m_pOutline->SetBrushColor(m_DefaultColor);
}

bool UWidget_HotkeySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool bSuccess = false;

	if (UOperation_Slot* pOperSlot = Cast<UOperation_Slot>(InOperation))
	{
		if (UWidget_InventorySlot* pInventorySlot = Cast<UWidget_InventorySlot>(pOperSlot->GetDraggedSlot()))
		{
			if (pInventorySlot->GetSlotInfo()->pItem->GetInfo().bCanUsed)
			{
				if (UWidget_HotkeySlot* pHotkeySlot = pInventorySlot->GetHotkeySlotWidget())
				{
					pHotkeySlot->SetAssignedWidget(nullptr);
					pHotkeySlot->UpdateWidget();
				}
				pInventorySlot->SetHotkeySlotWidget(this);
				m_pAssignedWidget = pInventorySlot;
				UpdateWidget();
				bSuccess = true;
			}

		}
		else if (UWidget_SkillEntry* pSkillEntry = Cast<UWidget_SkillEntry>(pOperSlot->GetDraggedSlot()))
		{
			if (ASkill_Buff* pSkill = Cast<ASkill_Buff>(pSkillEntry->GetSkill()))
			{
				pSkill->SetHotkeySlotWidget(this);
				m_pAssignedWidget = pSkillEntry;
				UpdateWidget();
				bSuccess = true;
			}
		}
	}
	m_pOutline->SetBrushColor(m_DefaultColor);
	return bSuccess;
}


#undef LOCTEXT_NAMESPACE


