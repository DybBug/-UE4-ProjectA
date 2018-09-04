// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_Base.h"
#include "Widget_Stat.generated.h"

/**
 * 
 */
class UButton;
class UVerticalBox;
class UTextBlock;
class UWidget_Main;
class UWidget_StatEntry;
class UComponent_Stat;

UCLASS()
class PROJECTA_API UWidget_Stat : public UWidget_Base
{
	GENERATED_BODY()
	
protected :
	virtual void  NativeConstruct() override;

protected :
	UPROPERTY()
	UButton* m_pCloseButton;

	UPROPERTY()
	UVerticalBox* m_pStatList;

	UPROPERTY()
	UTextBlock* m_pStatPointText;

	UPROPERTY()
	UButton* m_pApplyButton;

	UPROPERTY()
	UButton* m_pCancelButton;

	//
	//
	//
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_StatEntry> m_EntryWidgetClass;

	UComponent_Stat* m_pStat;

	int m_StatPoint;
	int m_UsedStatPoint;

public :
	void InitWidget(UWidget_Main* _pMainWidget, UComponent_Stat* _pStat);
	void UpdateWidget(int _Point);

	void ModifyStatPoint(int _Value);

	/* Get */
	FORCEINLINE const int& GetStatPoint() const { return m_StatPoint; }
	FORCEINLINE const int& GetUsedStatPoint() const { return m_UsedStatPoint; }

	/* Set */
	

public:
	void GenerateStatEntries();	

private :
	UFUNCTION()
	void _OnCloseButtonClicked();

	UFUNCTION()
	void _OnApplyButtonClicked();

	UFUNCTION()
	void _OnCancelButtonClicked();
};
