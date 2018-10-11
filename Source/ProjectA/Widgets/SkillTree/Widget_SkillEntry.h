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
class UTextBlock;
class UBorder;
class ASkill_Base;
class UWidget_SkillTree;
class UComponent_SkillTree;


UCLASS()
class PROJECTA_API UWidget_SkillEntry : public UUserWidget
{
	GENERATED_BODY()

protected :
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected :
	UPROPERTY()
	UBorder* m_pBorder;

	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UTextBlock* m_pLevelText;

	UPROPERTY()
	UVerticalBox* m_pButtonBox;

	UPROPERTY()
	UButton* m_pPlusButton;

	UPROPERTY()
	UButton* m_pMinusButton;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FLinearColor m_DefaultColor;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FLinearColor m_OverlapColor;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<ASkill_Base> m_SkillClass;

	UPROPERTY()
	ASkill_Base* m_pSkill;
	
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TArray<UWidget_SkillEntry*> m_pNextEntries;

	UWidget_SkillEntry* m_pPrevEntry;

	bool m_bCanLearnt;

	UWidget_SkillTree* m_pSkillTreeWidget;

	UComponent_SkillTree* m_pSkillTree;

public :
	void InitWidget(UWidget_SkillTree* _pSkillTree);
	void UpdateWidget();

	/* Get */
	FORCEINLINE const bool& GetCanLearnt() const { return m_bCanLearnt;  }

	FORCEINLINE ASkill_Base* const& GetSkill() const { return m_pSkill; }
	FORCEINLINE UWidget_SkillEntry* const& GetPrevEntry() const { return m_pPrevEntry; }

	/* Set */
	FORCEINLINE void SetCanLearnt(const bool& _bEnable) { m_bCanLearnt = _bEnable; }

	FORCEINLINE void SetPrevEntry(UWidget_SkillEntry* _pEntry) { m_pPrevEntry = _pEntry; }
protected :
	virtual void NativeOnMouseEnter(const FGeometry& _InGeometry, const FPointerEvent& _InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& _InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;


private :
	void _Learning();
	void _Upgrade();
	void _Downgrade();

	bool _Active();
	void _Disable();

	UFUNCTION()
	void _OnPlusButtonClicked();

	UFUNCTION()
	void _OnMinusButtonClicked();
	
	
};
