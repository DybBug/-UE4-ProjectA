// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_CraftingScreen.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;
class UUniformGridPanel;
class UVerticalBox;
class UButton;
class UWidget_Recipe;
class UComponent_Crafting;

struct FCrafting_Info;
enum class EStat_Types : uint8;

UCLASS()
class PROJECTA_API UWidget_CraftingScreen : public UUserWidget
{
	GENERATED_BODY()

protected  :
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected :
	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY()
	UTextBlock* m_pNameText;

	UPROPERTY()
	UTextBlock* m_pDescriptionText;

	UPROPERTY()
	UUniformGridPanel* m_pAbilityList;

	UPROPERTY()
	UVerticalBox* m_pRecipeList;

	UPROPERTY()
	UButton* m_pMakingButton;

	UPROPERTY()
	UButton* m_pCancelButton;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_Recipe> m_RecipeWidgetClass;

	UComponent_Crafting* m_pCrafting;

	FCrafting_Info m_CraftingInfo;

	bool m_bIsShow;


public :
	void InitWidget(UComponent_Crafting* _pComp);
	void UpdateWidget();

	void Show(const FCrafting_Info& _CraftingInfo);
	void Hide();

	/* Get */
	FORCEINLINE const bool& GetIsShow() const { return m_bIsShow; }

protected :
	void _SetupAbilityList();
	void _SetupRecipeList();

	UFUNCTION()
	void _OnMakingButtonClicked();

	UFUNCTION()
	void _OnCancelButtonClicked();
	
};
