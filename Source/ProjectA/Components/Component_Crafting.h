// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Component_Base.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting_Info")
	TSubclassOf<AItem_Base> CraftItemClass;

	// #. 아이템 재료 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting_Info")
	TMap<TSubclassOf<AItem_Base>, int> RecipeList;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Crafting : public UComponent_Base
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
	TArray<FCrafting_Info> m_CraftingItems;

public :
	virtual void InitComponent(UWidget_Base* _pWidget) override;
	virtual void UpdateComponent() override;

	bool CreateItemAt(int _Index);

	/* Get */
	FORCEINLINE const TArray<FCrafting_Info>& GetCraftingItems() const { return m_CraftingItems; }
	FORCEINLINE const FCrafting_Info& GetCraftingItemAt(int _Index) const { return m_CraftingItems[_Index]; }

};

