// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_ComboSlot.generated.h"

class UBorder;
class UImage;
class ASkill_Base;
class UComponent_SkillTree;

/**
 * 
 */
UCLASS()
class PROJECTA_API UWidget_ComboSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	virtual void NativePreConstruct() override;
	
protected :
	UPROPERTY()
	UBorder* m_pBorder;

	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FLinearColor m_DefaultColor;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FLinearColor m_OverlapColor;

	UComponent_SkillTree* m_pSkillTree;
	int m_Index;

public :
	void InitWidget(UComponent_SkillTree* _pSkillTree, int _Index);
	void UpdateWidget();

protected :
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;	
};
