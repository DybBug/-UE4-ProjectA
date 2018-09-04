// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectA_Enums.h"
#include "Component_Crafting.generated.h"


class UWidget_Crafting;
class AItem_Base;

USTRUCT(BlueprintType)
struct FCrafting_Info
{
	GENERATED_BODY()

public :
	// #. 제작 아이템.
	UPROPERTY(EditAnywhere, Category = "Crafting_Info")
	TSubclassOf<AItem_Base> CraftItemClass;

	// #. 아이템 재료 목록
	UPROPERTY(EditAnywhere, Category = "Crafting_Info")
	TMap<TSubclassOf<AItem_Base>, int> RecipeList;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Crafting : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Crafting();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected :
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TArray<FCrafting_Info> m_pCraftingItems;

	UWidget_Crafting* m_pCraftingWidget;

	bool m_bIsOpen;

public :
	void InitComponent(UWidget_Crafting* _pWidget);
	void UpdateComponent();

	bool CreateItem(const FCrafting_Info& _Crafting_Info);

	void Open();
	void Close();

	/* Get */
	FORCEINLINE const bool& GetIsOpen() const { return m_bIsOpen; }
	FORCEINLINE const TArray<FCrafting_Info>& GetCraftingItems() const { return m_pCraftingItems; }

	/* Set */
	FORCEINLINE void SetIsOpen(const bool& _bIsOpen) { m_bIsOpen = _bIsOpen; }
};

