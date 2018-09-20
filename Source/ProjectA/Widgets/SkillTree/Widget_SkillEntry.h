// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SkillEntry.generated.h"

/**
 * 
 */
class UImage;
class UButton;
class UVerticalBox;
class ASkill_Base;


UCLASS()
class PROJECTA_API UWidget_SkillEntry : public UUserWidget
{
	GENERATED_BODY()

protected :
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
protected :
	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UVerticalBox* m_pButtonBox;

	UPROPERTY()
	UButton* m_pPlusButton;

	UPROPERTY()
	UButton* m_pMinusButton;	

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<ASkill_Base> m_SkillClass;

public :

private :
	UFUNCTION()
	void _OnPlusButtonClicked();

	UFUNCTION()
	void _OnMinusButtonClicked();
	
	
};
