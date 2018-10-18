// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_BuffIcon.generated.h"

/**
 * 
 */
class UImage;
class UTexture2D;
class UMaterialInstanceDynamic;

UCLASS()
class PROJECTA_API UWidget_BuffIcon : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

protected :
	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UImage* m_pDuration;

	UPROPERTY()
	UMaterialInstanceDynamic* m_pDynamicMaterial;

public :
	void InitWidget(UTexture2D* _pTexture);
	void UpdateWidget(float _Percent);


	
};
