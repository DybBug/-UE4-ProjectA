// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SkillEntry.h"
#include "Widget_SkillTree.h"
#include "Skills/Skill_Base.h"
#include "Widget_SkillCategory.h"
#include "Components/Component_SkillTree.h"
#include "Operations/Operation_Slot.h"

#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/VerticalBox.h>
#include <Components/Border.h>
#include <WidgetTree.h>

void UWidget_SkillEntry::NativePreConstruct()
{
	if (IsValid(m_SkillClass))
	{
		const FSkill_Info& Info = m_SkillClass.GetDefaultObject()->GetInfo();
		m_pIcon->SetBrushFromTexture(Info.pIcon);
	}

	m_pBorder->SetBrushColor(m_DefaultColor);
}

void UWidget_SkillEntry::NativeConstruct()
{
	m_bCanLearnt = false;
	m_pPrevEntry = nullptr;
	m_pButtonBox->SetVisibility(ESlateVisibility::Collapsed);
	m_pPlusButton->SetIsEnabled(false);
	m_pMinusButton->SetIsEnabled(false);
	m_pLevelText->SetVisibility(ESlateVisibility::Hidden);

	m_pPlusButton->OnClicked.AddDynamic(this, &UWidget_SkillEntry::_OnPlusButtonClicked);
	m_pMinusButton->OnClicked.AddDynamic(this, &UWidget_SkillEntry::_OnMinusButtonClicked);
}

void UWidget_SkillEntry::InitWidget(UWidget_SkillTree* _pSkillTree)
{
	m_pSkillTreeWidget = _pSkillTree;
	m_pSkillTree = Cast<UComponent_SkillTree>(m_pSkillTreeWidget->GetComponent());

	for (auto& NextEntry : m_pNextEntries)
	{
		NextEntry->SetPrevEntry(this);
	}

	if (!m_pPrevEntry)
	{
		m_bCanLearnt = true;
	}
	UpdateWidget();
}

void UWidget_SkillEntry::UpdateWidget()
{
	m_bCanLearnt ? _Active() : _Disable();
}


void UWidget_SkillEntry::NativeOnMouseEnter(const FGeometry& _InGeometry, const FPointerEvent& _InMouseEvent)
{
	m_pBorder->SetBrushColor(m_OverlapColor);
}

void UWidget_SkillEntry::NativeOnMouseLeave(const FPointerEvent& _InMouseEvent)
{
	m_pBorder->SetBrushColor(m_DefaultColor);
}

FReply UWidget_SkillEntry::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (m_pSkill)
	{
		if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			FReply Result(FReply::Handled());
			Result.DetectDrag(this->TakeWidget(), EKeys::LeftMouseButton);
			return Result;
		}
	}

	return FReply::Unhandled();
}

void UWidget_SkillEntry::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	UOperation_Slot* pOper_Slot = NewObject<UOperation_Slot>(UOperation_Slot::StaticClass());
	pOper_Slot->InitOperation(this);
	pOper_Slot->DefaultDragVisual = m_pIcon;
	pOper_Slot->Pivot = EDragPivot::MouseDown;

	OutOperation = pOper_Slot;	
}

void UWidget_SkillEntry::_Learning()
{
	if (!m_pSkill)
	{
		m_pSkill = GetWorld()->SpawnActor<ASkill_Base>(m_SkillClass);
		m_pSkill->InitSkill(m_pSkillTree);
		m_pSkill->Upgrade();

		int SkillLevel = m_pSkill->GetInfo().CurrentLevel;
		m_pLevelText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_pLevelText->SetText(FText::AsNumber(SkillLevel));

		for (auto& NextEntry : m_pNextEntries)
		{
			NextEntry->SetCanLearnt(true);
		}

		m_pSkillTree->AddSkillPoint(-1);
	}
}

void UWidget_SkillEntry::_Upgrade()
{
	m_pSkill->Upgrade();

	int SkillLevel = m_pSkill->GetInfo().CurrentLevel;

	m_pLevelText->SetText(FText::AsNumber(SkillLevel));

	m_pSkillTree->AddSkillPoint(-1);

	_Active();
}

void UWidget_SkillEntry::_Downgrade()
{
	m_pSkill->Downgrade();

	int SkillLevel = m_pSkill->GetInfo().CurrentLevel;

	m_pLevelText->SetText(FText::AsNumber(SkillLevel));

	m_pSkillTree->AddSkillPoint(1);

	m_pPlusButton->SetIsEnabled(true);

	if (SkillLevel == 0)
	{
		m_pSkill->Destroy();
		m_pSkill = nullptr;
		m_pLevelText->SetVisibility(ESlateVisibility::Hidden);

		if (m_pPrevEntry)
		{
			m_pPrevEntry->UpdateWidget();
		}

		for (auto& NextEntry : m_pNextEntries)
		{
			NextEntry->SetCanLearnt(false);
			NextEntry->UpdateWidget();
		}
	}

	_Active();
}

bool UWidget_SkillEntry::_Active()
{
	if (m_bCanLearnt)
	{
		SetIsEnabled(true);

		int SkillPoint = m_pSkillTree->GetSkillPoint();
		if (SkillPoint)
		{
			m_pButtonBox->SetVisibility(ESlateVisibility::Visible);

			// #. ( +, - )버튼 활성/비활성.
			if (m_pSkill)
			{
				// #. - 버튼 활성/비활성.
				if (m_pSkill->GetInfo().CurrentLevel == 1)
				{
					// #. 다음 스킬이 있을 경우.
					for (auto& NextEntry : m_pNextEntries)
					{
						if (NextEntry->GetSkill())
						{
							m_pMinusButton->SetIsEnabled(false);
							return true;
						}						
					}

					// #. 다음 스킬이 없을 경우.
					m_pMinusButton->SetIsEnabled(true);
				}
				else
				{
					m_pMinusButton->SetIsEnabled(true);
				}

				// #. + 버튼 활성/비활성.
				if (m_pSkill->GetInfo().CurrentLevel < m_pSkill->GetInfo().MaxLevel)
				{
					m_pPlusButton->SetIsEnabled(true);
				}
				else
				{
					m_pPlusButton->SetIsEnabled(false);
				}
			}
			else
			{
				m_pPlusButton->SetIsEnabled(true);
				m_pMinusButton->SetIsEnabled(false);
			}					
		}
		else
		{
			m_pButtonBox->SetVisibility(ESlateVisibility::Collapsed);
		}
		return true;
	}

	return false;
}

void UWidget_SkillEntry::_Disable()
{
	m_pPlusButton->SetIsEnabled(false);
	m_pMinusButton->SetIsEnabled(false);
	m_pButtonBox->SetVisibility(ESlateVisibility::Collapsed);
	SetIsEnabled(false);
}

void UWidget_SkillEntry::_OnPlusButtonClicked()
{
	if (m_pSkill)
	{
		_Upgrade();
	}
	else
	{
		_Learning();
	}
}

void UWidget_SkillEntry::_OnMinusButtonClicked()
{
	_Downgrade();
}




