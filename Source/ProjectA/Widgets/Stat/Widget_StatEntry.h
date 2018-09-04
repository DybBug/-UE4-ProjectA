// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectA_Enums.h"
#include "Components/Component_Stat.h"
#include "Widget_StatEntry.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;
class UComponent_Stat;

struct FStat_Info;


UCLASS()
class PROJECTA_API UWidget_StatEntry : public UUserWidget
{
	GENERATED_BODY()

protected :
	virtual void NativeConstruct() override;

protected :
	UPROPERTY()
	UTextBlock* m_pStatText;

	UPROPERTY()
	UTextBlock* m_pCurrentText;

	UPROPERTY()
	UTextBlock* m_pSlashText;

	UPROPERTY()
	UTextBlock* m_pMaxText;

	UPROPERTY()
	UButton* m_pPlusButton;

	UPROPERTY()
	UButton* m_pMinusButton;

	//
	//
	//
	EStat_Types m_StatType;
	FStat_Info m_StatInfo;
	UComponent_Stat* m_pStat;

public :
	void InitWidget(const EStat_Types& _Type, UComponent_Stat* _pStat);
	void UpdateWidget(const FStat_Info& _StatInfo);
	void UpdateButtons();
	void UpdateStatColor();

	void ResetStat();

	void OnActivePlusButton(bool _bActive, ESlateVisibility _Visibility);
	void OnActiveMinusButton(bool _bActive, ESlateVisibility _Visibility);	

	/* Get */
	FORCEINLINE const EStat_Types& GetStatType() const { return m_StatType; }
	FORCEINLINE const FStat_Info& GetStatInfo() const { return m_StatInfo; }

protected :
	void _IncreaseStat();
	void _DecreaseStat();

	void _UpdatePlusButton();
	void _UpdateMinusButton();

	UFUNCTION()
	void _OnPlusButtonClicked();

	UFUNCTION()
	void _OnMinusButtonClicked();	
};
