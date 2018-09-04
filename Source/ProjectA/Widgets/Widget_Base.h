// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Base.generated.h"

/**
 * 
 */
class UButton;
class UWidget_Main;

UCLASS()
class PROJECTA_API UWidget_Base : public UUserWidget
{
	GENERATED_BODY()

protected :
	UWidget_Main* m_pMainWidget;

public :
	void InitWidget(UWidget_Main* _pMainWidget);
	
protected :
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

};
