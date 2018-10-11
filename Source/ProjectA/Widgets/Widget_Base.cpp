// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Base.h"
#include "Operations/Operation_Widget.h"
#include "Components/Component_Base.h"

#include <Components/Button.h>


void UWidget_Base::InitWidget(UWidget_Main* _pMainWidget, UComponent_Base* _pComponent)
{
	m_pMainWidget = _pMainWidget;
	m_pComponent = _pComponent;
}

void UWidget_Base::UpdateWidget()
{

}

FReply UWidget_Base::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FReply Result(FReply::Handled());
	Result.DetectDrag(this->TakeWidget(), EKeys::LeftMouseButton);
	return Result;
}

void UWidget_Base::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// #. ��ũ�� ���������� ���콺 ��ġ.
	FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();

	// #. ���� ��ǥ(���콺 ��ġ)�� (Geometry)���� ��ǥ�� ��ȯ.
	FVector2D LocalPos = InGeometry.AbsoluteToLocal(MousePos);

	// #. ���� DragDropOperation ����.
	UOperation_Widget* pOper_Widget = NewObject<UOperation_Widget>(UOperation_Widget::StaticClass());
	pOper_Widget->InitOperation(m_pMainWidget, this, LocalPos);
	pOper_Widget->DefaultDragVisual = this;
	pOper_Widget->Pivot = EDragPivot::MouseDown;

	// #. ���� ���� ����.
	RemoveFromParent();

	OutOperation = pOper_Widget;
}


