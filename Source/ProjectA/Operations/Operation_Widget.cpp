// Fill out your copyright notice in the Description page of Project Settings.

#include "Operation_Widget.h"
#include "Widgets/Widget_Main.h"

#include <Blueprint/UserWidget.h>



void UOperation_Widget::InitOperation(UWidget_Main* _pMainWidget, UUserWidget* _pDraggedWidget, const FVector2D& _Offset)
{
	m_pMainWidget = _pMainWidget;
	m_pDraggedWidget = _pDraggedWidget;
	m_Offset = _Offset;
}

void UOperation_Widget::Drop_Implementation(const FPointerEvent& PointerEvent)
{
	if (m_pMainWidget)
	{
		// #. ��ũ�� ������ ���콺 ��ġ.	
		FVector2D MousePos = PointerEvent.GetScreenSpacePosition();

		// #. ���� ��ǥ(��ũ���� ���콺 ��ġ)�� ���� ��ǥ(���� ������ ��ǥ)�� ��ȯ.
		FVector2D LocalPos = m_pMainWidget->GetCachedGeometry().AbsoluteToLocal(MousePos);

		FVector2D Pos = LocalPos - m_Offset;

		m_pDraggedWidget->AddToViewport();
		m_pDraggedWidget->SetPositionInViewport(Pos, false);
	}
}

void UOperation_Widget::DragCancelled_Implementation(const FPointerEvent& PointerEvent)
{
	if (m_pMainWidget)
	{
		// #. ��ũ�� ������ ���콺 ��ġ.
		FVector2D MousePos = PointerEvent.GetScreenSpacePosition();

		// #. ���� ��ǥ(��ũ���� ���콺 ��ġ)�� ���� ��ǥ(���� ������ ��ǥ)�� ��ȯ.
		FVector2D LocalPos = m_pMainWidget->GetCachedGeometry().AbsoluteToLocal(MousePos);

		FVector2D Pos = LocalPos - m_Offset;

		m_pDraggedWidget->AddToViewport();
		m_pDraggedWidget->SetPositionInViewport(Pos, false);
	}
}

void UOperation_Widget::Dragged_Implementation(const FPointerEvent& PointerEvent)
{

}
