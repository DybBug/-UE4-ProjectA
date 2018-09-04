// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_Base.h"
#include "Widget_Equipment.generated.h"

/**
 * 
 */
class UButton;
class UWidget_EquipmentSlot;
class UWidget_Main;
class UComponent_Equipment;

UCLASS()
class PROJECTA_API UWidget_Equipment : public UWidget_Base
{
	GENERATED_BODY()

protected :
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
protected :
	UPROPERTY()
	UButton* m_pCloseButton;

	UPROPERTY()
	UWidget_EquipmentSlot* m_pWeaponSlot;

	UPROPERTY()
	UWidget_EquipmentSlot* m_pSecondaryWeaponSlot;

	UPROPERTY()
	UWidget_EquipmentSlot* m_pNecklaceSlot;

	UPROPERTY()
	UWidget_EquipmentSlot* m_pEarringSlot_L;

	UPROPERTY()
	UWidget_EquipmentSlot* m_pEarringSlot_R;

	UPROPERTY()
	UWidget_EquipmentSlot* m_pBeltSlot;

	UPROPERTY()
	UWidget_EquipmentSlot* m_pRingSlot_L;

	UPROPERTY()
	UWidget_EquipmentSlot* m_pRingSlot_R;

	//
	// ..
	//
	UComponent_Equipment* m_pEquipment;

public :
	void InitWidget(UWidget_Main* _pMainWidget, UComponent_Equipment* _pEquipment);
	
	/* Get */
	FORCEINLINE UWidget_EquipmentSlot* const& GetWeaponSlot()          const { return m_pWeaponSlot; }
	FORCEINLINE UWidget_EquipmentSlot* const& GetSecondaryWeaponSlot() const { return m_pSecondaryWeaponSlot; }
	FORCEINLINE UWidget_EquipmentSlot* const& GetNecklaceSlot()        const { return m_pNecklaceSlot; }
	FORCEINLINE UWidget_EquipmentSlot* const& GetEarringSlot_L()       const { return m_pEarringSlot_L; }
	FORCEINLINE UWidget_EquipmentSlot* const& GetEarringSlot_R()       const { return m_pEarringSlot_R; }
	FORCEINLINE UWidget_EquipmentSlot* const& GetBeltSlot()            const { return m_pBeltSlot; }
	FORCEINLINE UWidget_EquipmentSlot* const& GetRingSlot_L()          const { return m_pRingSlot_L; }
	FORCEINLINE UWidget_EquipmentSlot* const& GetRingSlot_R()          const { return m_pRingSlot_R; }

protected :
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UFUNCTION()
	void _OnCloseButtonClicked();
															          
};
