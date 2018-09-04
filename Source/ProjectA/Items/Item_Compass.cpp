// Fill out your copyright notice in the Description page of Project Settings.

#include "Item_Compass.h"
#include "Widgets/Widget_Main.h"
#include "Widgets/Misc/Widget_Compass.h"
#include "Players/Player_Character.h"

#include <TimerManager.h>

AItem_Compass::AItem_Compass()
{
	m_pCompassWidget = nullptr;
}


void AItem_Compass::InitItem(AActor* _pOwner)
{
	AItem_Base::InitItem(_pOwner);
}

bool AItem_Compass::OnUse(FInventorySlot_Info* const pSlotInfo)
{
	if (m_pPlayer)
	{
		if (!m_pCompassWidget)
		{
			m_pCompassWidget = m_pPlayer->GetMainWidget()->GetCompassWidget();
		}

		AItem_Compass* pPrevCompass = m_pCompassWidget->GetCurrentCompass();

		pPrevCompass ? pPrevCompass->Close() : Open();

		return true;
	}
	return false;
}

void AItem_Compass::Open()
{
	if (AItem_Compass* pPrevCompass = m_pCompassWidget->GetCurrentCompass())
	{
		pPrevCompass->Close();
	}
		m_pCompassWidget->Show(this);

		GetWorld()->GetTimerManager().SetTimer(m_hCompassTimer, this, &AItem_Compass::_UpdateCompass, 0.02f, true);
}

void AItem_Compass::Close()
{
	GetWorld()->GetTimerManager().ClearTimer(m_hCompassTimer);
	m_pCompassWidget->Hide();
	m_pCompassWidget->SetCurrentCompass(nullptr);
	m_pCompassWidget = nullptr;
}

void AItem_Compass::_UpdateCompass()
{
	FRotator CtrRot = m_pPlayer->GetControlRotation();

	CtrRot.Yaw -= (CtrRot.Yaw > 180.f) ?  360.f : 0.f;

	m_pCompassWidget->UpdateWidget(CtrRot.Yaw);
}

