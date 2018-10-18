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
class UComponent_Base;

UCLASS()
class PROJECTA_API UWidget_Base : public UUserWidget
{
	GENERATED_BODY()

protected :
	UWidget_Main* m_pMainWidget;
	UComponent_Base* m_pComponent;

public :
	virtual void InitWidget(UWidget_Main* _pMainWidget, UComponent_Base* _pComponent); 
	virtual void UpdateWidget();

	/* Get */
	FORCEINLINE UWidget_Main*    const& GetMainWidget() const { return m_pMainWidget; }
	FORCEINLINE UComponent_Base* const& GetComponent()  const { return m_pComponent; }

	/* Set */
	FORCEINLINE void SetMainWidget(UWidget_Main* _pMainWidget)  { m_pMainWidget = _pMainWidget; }
	FORCEINLINE void SetComponent(UComponent_Base* _pComponent) { m_pComponent = _pComponent; }
	
protected :
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

};
