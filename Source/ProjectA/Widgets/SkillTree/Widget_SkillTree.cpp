// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_SkillTree.h"
#include "Widgets/Widget_Main.h"
#include "Widget_SkillDetail.h"
#include "Widget_SkillCategory.h"
#include "Widget_ComboSlot.h"
#include "Components/Component_SkillTree.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/WidgetSwitcher.h>
#include <Components/HorizontalBox.h>

void UWidget_SkillTree::NativePreConstruct()
{
	if (m_ComboSlotWidgetClass)
	{
		m_pComboList->ClearChildren();

		for (int i = 0; i < m_ComboCount; ++i)
		{
			UWidget_ComboSlot* pComboWidget = CreateWidget<UWidget_ComboSlot>(this, m_ComboSlotWidgetClass);
			m_pComboList->AddChild(pComboWidget);
		}
	}
}

void UWidget_SkillTree::NativeConstruct()
{
	m_pCloseButton->OnClicked.AddDynamic(this, &UWidget_SkillTree::_OnCloseButtonClicked);
	m_pActiveButton->OnClicked.AddDynamic(this, &UWidget_SkillTree::_OnActiveButtonClicked);
	m_pBuffButton->OnClicked.AddDynamic(this, &UWidget_SkillTree::_OnBuffButtonClicked);
	m_pPassiveButton->OnClicked.AddDynamic(this, &UWidget_SkillTree::_OnPassiveButtonClicked);
}

void UWidget_SkillTree::InitWidget(UWidget_Main* _pMain, UComponent_Base* _pComponent)
{
	UWidget_Base::InitWidget(_pMain, _pComponent);

	UComponent_SkillTree* pComp = Cast<UComponent_SkillTree>(m_pComponent);

	if (m_SkillDetailWidgetClass)
	{
		m_pSkillDetailWidget = CreateWidget<UWidget_SkillDetail>(this, UWidget_SkillDetail::StaticClass());
	}

	for (int i = 0; i < m_pSkillCategoryList->GetChildrenCount(); ++i)
	{
		UWidget_SkillCategory* pCategory = Cast<UWidget_SkillCategory>(m_pSkillCategoryList->GetChildAt(i));
		pCategory->InitWidget(this);
	}

	for (int i = 0; i < m_pComboList->GetChildrenCount(); ++i)
	{
		UWidget_ComboSlot* pComboSlot = Cast<UWidget_ComboSlot>(m_pComboList->GetChildAt(i));
		pComboSlot->InitWidget(pComp, i);
	}

	int SkillPoint = pComp->GetSkillPoint();

	m_pPointText->SetText(FText::AsNumber(SkillPoint));
}

void UWidget_SkillTree::UpdateWidget()
{
	UComponent_SkillTree* pComp = Cast<UComponent_SkillTree>(m_pComponent);
	int SkillPoint = pComp->GetSkillPoint();

	m_pPointText->SetText(FText::AsNumber(SkillPoint));

	UWidget_SkillCategory* pSkillCategory = Cast<UWidget_SkillCategory>(m_pSkillCategoryList->GetActiveWidget());
	pSkillCategory->UpdateWidget();
}

FReply UWidget_SkillTree::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidget_Base::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}

	return FReply::Unhandled();
}

bool UWidget_SkillTree::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return true;
}

void UWidget_SkillTree::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	return UWidget_Base::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UWidget_SkillTree::_OnCloseButtonClicked()
{
	m_pComponent->Close();
}

void UWidget_SkillTree::_OnActiveButtonClicked()
{
	m_pSkillCategoryList->SetActiveWidgetIndex(0);
	UWidget_SkillCategory* pCategoryWidget = Cast<UWidget_SkillCategory>(m_pSkillCategoryList->GetActiveWidget());
	pCategoryWidget->UpdateWidget();
}

void UWidget_SkillTree::_OnBuffButtonClicked()
{
	m_pSkillCategoryList->SetActiveWidgetIndex(1);
	UWidget_SkillCategory* pCategoryWidget = Cast<UWidget_SkillCategory>(m_pSkillCategoryList->GetActiveWidget());
	pCategoryWidget->UpdateWidget();
}

void UWidget_SkillTree::_OnPassiveButtonClicked()
{
	m_pSkillCategoryList->SetActiveWidgetIndex(2);
	UWidget_SkillCategory* pCategoryWidget = Cast<UWidget_SkillCategory>(m_pSkillCategoryList->GetActiveWidget());
	pCategoryWidget->UpdateWidget();
}



