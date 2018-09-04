// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item_Base.h"
#include "ProjectA_Enums.h"
#include "Item_Equipment.generated.h"

/**
 * 
 */
class UArrowComponent;
class UStaticMeshComponent;



UCLASS()
class PROJECTA_API AItem_Equipment : public AItem_Base
{
	GENERATED_BODY()

public:
	AItem_Equipment();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* m_pArrow;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* m_pMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Configuration")
	FName m_SocketName;

	// #. 장비 유형.
	UPROPERTY(EditAnywhere, Category = "Configuration|Equipment")
	EEquipment_Types m_EquipmentType;

public:
	virtual void InitItem(AActor* _pOwner) override;
	virtual bool OnUse(FInventorySlot_Info* const pSlotInfo) override;

	/* Get */
	FORCEINLINE const EEquipment_Types& GetEquipmentType() const { return m_EquipmentType; }
	FORCEINLINE const FName&           GetSocketName()    const { return m_SocketName; }
};
