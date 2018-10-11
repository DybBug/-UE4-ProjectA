// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_Base.h"
#include "Widget_Compass.generated.h"

/**
 * 
 */
class UButton;
class UImage;
class UWidget_Main;
class AItem_Compass;

UCLASS()
class PROJECTA_API UWidget_Compass : public UWidget_Base
{
	GENERATED_BODY()

protected :
	virtual void NativeConstruct() override;

protected :
	UPROPERTY()
	UButton* m_pCloseButton;

	UPROPERTY()
	UImage* m_pArrow;

	AItem_Compass* m_pCurrentCompass;
	
public :
	virtual void InitWidget(UWidget_Main* _pMainWidget, UComponent_Base* _pComponent) override;
	virtual void UpdateWidget() override {};
	void UpdateWidget(float _Angle);

	void Show(AItem_Compass* m_pCurrCompass);
	void Hide();

	/* Get */
	FORCEINLINE AItem_Compass* const& GetCurrentCompass() const { return m_pCurrentCompass; }

	/* Set */
	FORCEINLINE void SetCurrentCompass(AItem_Compass* const& _pCompass) { m_pCurrentCompass = _pCompass; }

private :
	UFUNCTION()
	void _OnCloseButtonClicked();
	
};
