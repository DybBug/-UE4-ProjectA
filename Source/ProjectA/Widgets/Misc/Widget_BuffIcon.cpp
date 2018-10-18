// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_BuffIcon.h"

#include <Components/Image.h>
#include <Components/PanelWidget.h>
#include <Materials/MaterialInstanceDynamic.h>

void UWidget_BuffIcon::NativeConstruct()
{
	m_pDynamicMaterial = m_pDuration->GetDynamicMaterial();
}

void UWidget_BuffIcon::InitWidget(UTexture2D* _pTexture)
{
	m_pIcon->SetBrushFromTexture(_pTexture);
}

void UWidget_BuffIcon::UpdateWidget(float _Percent)
{
	m_pDynamicMaterial->SetScalarParameterValue("Percent", _Percent);
}




