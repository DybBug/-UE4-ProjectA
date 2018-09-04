// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_ThrowAway.h"
#include "Widgets/Widget_Main.h"
#include "Components/Component_Inventory.h"
#include "Items/Item_Base.h"

#include <Components/HorizontalBox.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <TimerManager.h>
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/InputSettings.h>



void UWidget_ThrowAway::NativeConstruct()
{
	m_CurrentThrowAmount = 1;
	m_MaxThrowAmount = 0;
	m_ClickCount = 0;

	m_pMinusButton->OnClicked.AddDynamic(this, &UWidget_ThrowAway::_OnMinusButtonClicked);
	m_pMinusButton->OnPressed.AddDynamic(this, &UWidget_ThrowAway::_OnMinusButtonPressed);
	m_pMinusButton->OnReleased.AddDynamic(this, &UWidget_ThrowAway::_OnMinusButtonReleased);

	m_pPlusButton->OnClicked.AddDynamic(this, &UWidget_ThrowAway::_OnPlusButtonClicked);
	m_pPlusButton->OnPressed.AddDynamic(this, &UWidget_ThrowAway::_OnPlusButtonPressed);
	m_pPlusButton->OnReleased.AddDynamic(this, &UWidget_ThrowAway::_OnPlusButtonReleased);


	m_pConfirmButton->OnClicked.AddDynamic(this, &UWidget_ThrowAway::_OnConfirmButtonClicked);
	m_pCancelButton->OnClicked.AddDynamic(this, &UWidget_ThrowAway::_OnCancelButtonClicked);
}

void UWidget_ThrowAway::InitWidget(UWidget_Main* _pMainWidget, UComponent_Inventory* _pInventory)
{
	UWidget_Base::InitWidget(_pMainWidget);

	m_pInventory = _pInventory;
}

void UWidget_ThrowAway::Show(FInventorySlot_Info* _pSlotInfo)
{
	m_pSlotInfo = _pSlotInfo;
	m_CurrentThrowAmount = 1;

	if (m_pSlotInfo->pItem)
	{
		FItem_Info ItemInfo = m_pSlotInfo->pItem->GetInfo();
		m_MaxThrowAmount = m_pSlotInfo->Amount;

		// #. 아이콘.
		m_pIcon->SetBrushFromTexture(ItemInfo.pIcon);

		// #. 이름.
		m_pNameText->SetText(FText::FromName(ItemInfo.Name));

		if (m_pSlotInfo->Amount > 1)
		{
			m_pAmountBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			// #. 수량.
			m_pAmountText->SetText(FText::AsNumber(1));

			// #. -버튼.
			m_pMinusButton->SetIsEnabled(false);

			// #. +버튼.
			m_pPlusButton->SetIsEnabled(true);
		}
		else
		{
			m_pAmountBox->SetVisibility(ESlateVisibility::Collapsed);	
		}

		SetVisibility(ESlateVisibility::Visible);
	}
}

void UWidget_ThrowAway::Hide()
{
	m_pSlotInfo = nullptr;
	SetVisibility(ESlateVisibility::Hidden);
}

FReply UWidget_ThrowAway::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidget_Base::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}

	return FReply::Unhandled();
}

void UWidget_ThrowAway::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	return UWidget_Base::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UWidget_ThrowAway::_IncreaseAmount()
{
	m_pMinusButton->SetIsEnabled(true);

	m_CurrentThrowAmount++;
	m_CurrentThrowAmount = FMath::Clamp<int>(m_CurrentThrowAmount, 1, m_MaxThrowAmount);

	m_pAmountText->SetText(FText::AsNumber(m_CurrentThrowAmount));

	if (m_CurrentThrowAmount == m_MaxThrowAmount)
	{
		m_pPlusButton->SetIsEnabled(false);
	}
}

void UWidget_ThrowAway::_DecreaseAmount()
{
	m_pPlusButton->SetIsEnabled(true);

	m_CurrentThrowAmount--;
	m_CurrentThrowAmount = FMath::Clamp<int>(m_CurrentThrowAmount, 1, m_MaxThrowAmount);

	m_pAmountText->SetText(FText::AsNumber(m_CurrentThrowAmount));

	if (m_CurrentThrowAmount == 1)
	{
		m_pMinusButton->SetIsEnabled(false);
	}
}

void UWidget_ThrowAway::_ResetClickCount()
{
	m_ClickCount = 0;
}

void UWidget_ThrowAway::_OnMinusButtonClicked()
{
	m_ClickCount++;

	FLatentActionInfo ActionInfo;
	ActionInfo.CallbackTarget = this;
	ActionInfo.ExecutionFunction = TEXT("_ResetClickCount");
	ActionInfo.Linkage = 1;
	ActionInfo.UUID = GetUniqueID();

	UKismetSystemLibrary::Delay(this, UInputSettings::GetInputSettings()->DoubleClickTime, ActionInfo);

	if (m_ClickCount >= 2)
	{
		m_ClickCount = 0;
		m_CurrentThrowAmount = 1;
		m_pAmountText->SetText(FText::AsNumber(m_CurrentThrowAmount));

		m_pPlusButton->SetIsEnabled(true);
		m_pMinusButton->SetIsEnabled(false);
	}
	else
	{
		_DecreaseAmount();
	}
}

void UWidget_ThrowAway::_OnMinusButtonPressed()
{
	GetWorld()->GetTimerManager().SetTimer(m_hMinusTimer, this, &UWidget_ThrowAway::_DecreaseAmount, 0.2f, true);
}

void UWidget_ThrowAway::_OnMinusButtonReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(m_hMinusTimer);
}

void UWidget_ThrowAway::_OnPlusButtonClicked()
{
	m_ClickCount++;

	FLatentActionInfo ActionInfo;
	ActionInfo.CallbackTarget = this;
	ActionInfo.ExecutionFunction = TEXT("_ResetClickCount");
	ActionInfo.Linkage = 1;
	ActionInfo.UUID = GetUniqueID();
	UKismetSystemLibrary::Delay(this, UInputSettings::GetInputSettings()->DoubleClickTime, ActionInfo);

	if (m_ClickCount >= 2)
	{
		m_ClickCount = 0;
		m_CurrentThrowAmount = m_MaxThrowAmount;
		m_pAmountText->SetText(FText::AsNumber(m_CurrentThrowAmount));

		m_pPlusButton->SetIsEnabled(false);
		m_pMinusButton->SetIsEnabled(true);
	}
	else
	{
		_IncreaseAmount();
	}
}

void UWidget_ThrowAway::_OnPlusButtonPressed()
{
	GetWorld()->GetTimerManager().SetTimer(m_hPlusTimer, this, &UWidget_ThrowAway::_IncreaseAmount, 0.2f, true);
}

void UWidget_ThrowAway::_OnPlusButtonReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(m_hPlusTimer);
}

void UWidget_ThrowAway::_OnConfirmButtonClicked()
{
	if (m_pInventory)
	{
		m_pInventory->ThrowAwayItem(m_pSlotInfo->SlotIndex, m_CurrentThrowAmount);
		Hide();
	}
}

void UWidget_ThrowAway::_OnCancelButtonClicked()
{
	Hide();
}
