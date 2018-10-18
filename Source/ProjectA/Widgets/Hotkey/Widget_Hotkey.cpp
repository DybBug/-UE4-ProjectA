// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Hotkey.h"
#include "Widget_HotkeySlot.h"

#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>



void UWidget_Hotkey::NativePreConstruct()
{
	if (m_HotkeySlotClass && m_ColumnCount)
	{
		m_pHotkeySlotList->ClearChildren();

		for (int i = 0; i < m_HotkeyList.Num(); ++i)
		{
			UWidget_HotkeySlot* pWidget = CreateWidget<UWidget_HotkeySlot>(this, m_HotkeySlotClass);
			pWidget->InitWidget(this, m_HotkeyList[i], i);

			UUniformGridSlot* pSlot = m_pHotkeySlotList->AddChildToUniformGrid(pWidget);
			pSlot->SetColumn(i % m_ColumnCount);
			pSlot->SetRow(i / m_ColumnCount);
		}
	}
}

void UWidget_Hotkey::PressKey(int _Index)
{
	UWidget_HotkeySlot* pHotkeySlot = Cast<UWidget_HotkeySlot>(m_pHotkeySlotList->GetChildAt(_Index));
	pHotkeySlot->Use();
}


