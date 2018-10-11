// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_Base.h"
#include "Widget_SkillTree.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
class UWidget_Main;
class UWidget_SkillDetail;
class UWidget_ComboSlot;
class UComponent_SkillTree;
class UWidgetSwitcher;
class UHorizontalBox;

UCLASS()
class PROJECTA_API UWidget_SkillTree : public UWidget_Base
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
protected :
	UPROPERTY()
	UButton* m_pCloseButton;

	UPROPERTY()
	UTextBlock* m_pPointText;

	UPROPERTY()
	UButton* m_pActiveButton;

	UPROPERTY()
	UButton* m_pBuffButton;

	UPROPERTY()
	UButton* m_pPassiveButton;

	UPROPERTY()
	UWidgetSwitcher* m_pSkillCategoryList;

	UPROPERTY()
	UHorizontalBox* m_pComboList;


	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_SkillDetail> m_SkillDetailWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_ComboSlot> m_ComboSlotWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	int m_ComboCount;

	UWidget_SkillDetail* m_pSkillDetailWidget;

	
public :
	virtual void InitWidget(UWidget_Main* _pMain, UComponent_Base* _pComponent) override;
	virtual void UpdateWidget() override;

	/* Get */
	FORCEINLINE UWidget_SkillDetail* const& GetSkillDetailWidget() const { return m_pSkillDetailWidget; }
	FORCEINLINE const int& GetComboCount() const { return m_ComboCount; }

protected :
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

private:
	UFUNCTION()
	void _OnCloseButtonClicked();

	UFUNCTION()
	void _OnActiveButtonClicked();

	UFUNCTION()
	void _OnBuffButtonClicked();

	UFUNCTION()
	void _OnPassiveButtonClicked();


};
