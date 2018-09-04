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
		// #. 스크린 공간의 마우스 위치.	
		FVector2D MousePos = PointerEvent.GetScreenSpacePosition();

		// #. 절대 좌표(스크린상 마우스 위치)를 로컬 좌표(메인 위젯의 좌표)로 변환.
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
		// #. 스크린 공간의 마우스 위치.
		FVector2D MousePos = PointerEvent.GetScreenSpacePosition();

		// #. 절대 좌표(스크린상 마우스 위치)를 로컬 좌표(메인 위젯의 좌표)로 변환.
		FVector2D LocalPos = m_pMainWidget->GetCachedGeometry().AbsoluteToLocal(MousePos);

		FVector2D Pos = LocalPos - m_Offset;

		m_pDraggedWidget->AddToViewport();
		m_pDraggedWidget->SetPositionInViewport(Pos, false);
	}
}

void UOperation_Widget::Dragged_Implementation(const FPointerEvent& PointerEvent)
{

}
