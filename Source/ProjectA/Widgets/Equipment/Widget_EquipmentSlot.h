// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectA_Enums.h"
#include "Widget_EquipmentSlot.generated.h"

/**
 * 
 */
class UBorder;
class UImage;
class UWidget_Detail;
class UComponent_Equipment;
class AItem_Equipment;

struct FEquipmentSlot_Info;


UCLASS()
class PROJECTA_API UWidget_EquipmentSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected :
	virtual void NativePreConstruct() override;

protected :
	UPROPERTY()
	UBorder* m_pOutline;

	UPROPERTY()
	UBorder* m_pBackground;

	UPROPERTY()
	UImage* m_pIcon;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	EEquipment_Types m_Type;

	UPROPERTY(EditAnywhere, Category = "Configuration|Outline")
	FLinearColor m_DefaultColor;

	UPROPERTY(EditAnywhere, Category = "Configuration|Outline")
	FLinearColor m_OverlapColor;

	UPROPERTY(EditAnywhere, Category = "Configuration|Outline")
	FLinearColor m_FailColor;

	UPROPERTY(EditAnywhere, Category = "Configuration|Background")
	UTexture2D* m_pBackgroundImage;

	const FEquipmentSlot_Info* m_pSlotInfo = nullptr;

	UComponent_Equipment* m_pEquipment;
	UWidget_Detail* m_pDetailWidget;

private :
	UComponent_Equipment * m_pEquipmentRef;
	typedef bool(UComponent_Equipment::*Equip)(AItem_Equipment*);
	Equip EquipFunc = nullptr;

	UComponent_Equipment* m_pUnEquipmentRef;
	typedef bool(UComponent_Equipment::*UnEquip)(void);
	UnEquip UnEquipFunc = nullptr;

public :
	void InitWidget(UComponent_Equipment* _pEquipment, UWidget_Detail* _pDetailWidget);
	void UpdateWidget();

	void Show();
	void Hide();

	void BindEquipFunc(UComponent_Equipment* _pComp, Equip _pFunc);
	void BindUnEquipFunc(UComponent_Equipment* _pComp, UnEquip _pFunc);


	/* Get */
	FORCEINLINE const EEquipment_Types& GetType() const { return m_Type; }

	/* Set */
	FORCEINLINE void SetSlotInfo(const FEquipmentSlot_Info* const& _pSlotInfo) { m_pSlotInfo = _pSlotInfo; }

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
