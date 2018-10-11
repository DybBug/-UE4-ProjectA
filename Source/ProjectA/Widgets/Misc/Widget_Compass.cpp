// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Compass.h"
#include "Widgets/Widget_Main.h"
#include "Items/Item_Compass.h"

#include <Components/Button.h>
#include <Components/Image.h>

void UWidget_Compass::NativeConstruct()
{
	m_pCloseButton->OnClicked.AddDynamic(this, &UWidget_Compass::_OnCloseButtonClicked);
}

void UWidget_Compass::InitWidget(UWidget_Main* _pMainWidget, UComponent_Base* _pComponent)
{
	UWidget_Base::InitWidget(_pMainWidget, _pComponent);
}

void UWidget_Compass::UpdateWidget(float _Angle)
{
	m_pArrow->SetRenderAngle(_Angle);
}

void UWidget_Compass::Show(AItem_Compass* _pCurrCompass)
{
	if (!m_pCurrentCompass)
	{
		m_pCurrentCompass = _pCurrCompass;
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UWidget_Compass::Hide()
{
	if (m_pCurrentCompass)
	{
		m_pCurrentCompass = nullptr;
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_Compass::_OnCloseButtonClicked()
{
	m_pCurrentCompass->Close();
}
