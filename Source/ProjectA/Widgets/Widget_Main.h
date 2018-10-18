// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectA_Enums.h"
#include "Widget_Main.generated.h"

/**
 * 
 */
class UWidget_Inventory;
class UWidget_Equipment;
class UWidget_Stat;
class UWidget_Pickup;
class UWidget_Detail;
class UWidget_ThrowAway;
class UWidget_StatBar;
class UWidget_Crafting;
class UWidget_Compass;
class UWidget_SkillTree;
class UWidget_Hotkey;
class UWidget_CastingBar;
class UWidget_BuffIcon;
class UHorizontalBox;
class ASkill_Buff;
class APlayer_Character;

UCLASS()
class PROJECTA_API UWidget_Main : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UWidget_Inventory* m_pInventoryWidget;

	UPROPERTY()
	UWidget_Equipment* m_pEquipmentWidget;

	UPROPERTY()
	UWidget_Stat* m_pStatWidget;

	UPROPERTY()
	UWidget_ThrowAway* m_pThrowAwayWidget;

	UPROPERTY()
	UWidget_Pickup* m_pPickupWidget;

	UPROPERTY()
	UWidget_StatBar* m_pHealthBarWidget;

	UPROPERTY()
	UWidget_StatBar* m_pManaBarWidget;

	UPROPERTY()
	UWidget_StatBar* m_pStaminaBarWidget;

	UPROPERTY()
	UWidget_Crafting* m_pCraftingWidget;

	UPROPERTY()
	UWidget_SkillTree* m_pSkillTreeWidget;

	UPROPERTY()
	UWidget_Hotkey* m_pHotkeyWidget;

	UPROPERTY()
	UWidget_Compass* m_pCompassWidget;

	UPROPERTY()
	UWidget_CastingBar* m_pCastingBarWidget;

	UPROPERTY()
	UHorizontalBox* m_pBuffList;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_Detail> m_DetailWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_BuffIcon> m_BuffIconWidgetClass;

	UPROPERTY()
	UWidget_Detail* m_pDetailWidget = nullptr;

	APlayer_Character* m_pPlayer;


public:
	bool InitWidget(APlayer_Character* _pPlayer);

	void AddBuff(ASkill_Buff* _pBuff);
	void ResetBuffAt(int i);
	void RemoveBuffAt(int i);

	void UpdateStatBar(EStat_Types _Type, float _CurrentValue, float _MaxValue);

	/* Get */
	FORCEINLINE UWidget_Inventory*  const& GetInventoryWidget()  const { return m_pInventoryWidget; }
	FORCEINLINE UWidget_Equipment*  const& GetEquipmentWidget()  const { return m_pEquipmentWidget; }
	FORCEINLINE UWidget_Stat*       const& GetStatWidget()       const { return m_pStatWidget; }
	FORCEINLINE UWidget_Detail*     const& GetDetailWidget()     const { return m_pDetailWidget; }
	FORCEINLINE UWidget_Pickup*     const& GetPickupWidget()     const { return m_pPickupWidget; }
	FORCEINLINE UWidget_StatBar*    const& GetHealthBarWidget()  const { return m_pHealthBarWidget; }
	FORCEINLINE UWidget_StatBar*    const& GetManaBarWidget()    const { return m_pManaBarWidget; }
	FORCEINLINE UWidget_StatBar*    const& GetStaminaBarWidget() const { return m_pStaminaBarWidget; }
	FORCEINLINE UWidget_Crafting*   const& GetCraftingWidget()   const { return m_pCraftingWidget; }
	FORCEINLINE UWidget_SkillTree*  const& GetSkillTreeWidget()  const { return m_pSkillTreeWidget; }
	FORCEINLINE UWidget_Hotkey*     const& GetHotkeyWidget()     const { return m_pHotkeyWidget; }
	FORCEINLINE UWidget_Compass*    const& GetCompassWidget()    const { return m_pCompassWidget; }
	FORCEINLINE UWidget_CastingBar* const& GetCastingBarWidget() const { return m_pCastingBarWidget; }

protected :
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
