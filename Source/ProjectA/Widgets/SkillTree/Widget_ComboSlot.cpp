// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_ComboSlot.h"
#include "Widget_SkillEntry.h"
#include "Skills/Skill_Active.h"
#include "Operations/Operation_Slot.h"
#include "Components/Component_SkillTree.h"

#include <Components/Border.h>
#include <Components/Image.h>


void UWidget_ComboSlot::NativePreConstruct()
{
	m_pBorder->SetBrushColor(m_DefaultColor);
}

void UWidget_ComboSlot::InitWidget(UComponent_SkillTree* _pSkillTree, int _Index)
{
	m_pSkillTree = _pSkillTree;
	m_Index = _Index;
}

void UWidget_ComboSlot::UpdateWidget()
{
	ASkill_Base* pSkill = m_pSkillTree->GetSkill(m_Index);
	if (pSkill)
	{
		m_pIcon->SetBrushFromTexture(pSkill->GetInfo().pIcon);
	}
	else
	{
		m_pIcon->SetBrushFromTexture(nullptr);
	}
	m_pBorder->SetBrushColor(m_DefaultColor);
}

void UWidget_ComboSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	m_pBorder->SetBrushColor(m_OverlapColor);
}

void UWidget_ComboSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	m_pBorder->SetBrushColor(m_DefaultColor);
}

FReply UWidget_ComboSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		if (m_Index == (m_pSkillTree->GetMaxCombo()-1))
		{
			m_pSkillTree->RemoveSkill(m_Index);
			UpdateWidget();
		}
	}

	return FReply::Unhandled();
}

void UWidget_ComboSlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UOperation_Slot* pOper_Slot = Cast<UOperation_Slot>(InOperation);
	if (pOper_Slot)
	{
		UWidget_SkillEntry* pSkillEntry = Cast<UWidget_SkillEntry>(pOper_Slot->GetDraggedSlot());

		if (Cast<ASkill_Active>(pSkillEntry->GetSkill()))
		{
			int Index = m_pSkillTree->HasSkill_In_SkillList(pSkillEntry->GetSkill()->GetClass());
			if (Index > -1)
			{
				m_pBorder->SetBrushColor(FColor::Red);
			}
			else if (m_Index > m_pSkillTree->GetMaxCombo())
			{
				m_pBorder->SetBrushColor(FColor::Red);
			}
			else
			{
				m_pBorder->SetBrushColor(m_OverlapColor);
			}
		}
		else
		{
			m_pBorder->SetBrushColor(FColor::Red);
		}
	}
}

void UWidget_ComboSlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	m_pBorder->SetBrushColor(m_DefaultColor);
}

bool UWidget_ComboSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (m_pBorder->BrushColor == FColor::Red)
	{
		return false;
	}

	UOperation_Slot* pOper_Slot = Cast<UOperation_Slot>(InOperation);
	if (pOper_Slot)
	{
		if (m_Index <= m_pSkillTree->GetMaxCombo())
		{
			UWidget_SkillEntry* pSkillEntry = Cast<UWidget_SkillEntry>(pOper_Slot->GetDraggedSlot());

			int Index = m_pSkillTree->HasSkill_In_SkillList(pSkillEntry->GetSkill()->GetClass());
			if (Index == -1)
			{
				m_pSkillTree->AddSkill(pSkillEntry->GetSkill(), m_Index);
				UpdateWidget();
			}		
			return true;
		}
	}
	return false;
}



