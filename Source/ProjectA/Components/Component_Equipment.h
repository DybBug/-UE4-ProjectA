// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_Equipment.generated.h"

class UWidget_Equipment;
class UWidget_EquipmentSlot;
class AItem_Equipment;

USTRUCT(BlueprintType)
struct FEquipmentSlot_Info
{
	GENERATED_BODY()
		
	FEquipmentSlot_Info() :
		pSlotWidget(nullptr), pItem(nullptr) {};

public :
	UPROPERTY(VisibleAnywhere, Category = "EquipmentSlot_Info")
	AItem_Equipment* pItem;

	UPROPERTY(VisibleAnywhere, Category = "EquipmentSlot_Info")
	UWidget_EquipmentSlot* pSlotWidget;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Equipment : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Equipment();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected :
	UWidget_Equipment* m_pEquipmentWidget;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlot_Info m_WeaponSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlot_Info m_SecondaryWeaponSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlot_Info m_NecklaceSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlot_Info m_BeltSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TArray<FEquipmentSlot_Info> m_RingSlots;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TArray<FEquipmentSlot_Info> m_EarringSlots;

	int m_RingIndex;
	int m_EarringIndex;

	bool m_bIsOpen;

public :
	void InitComponent(UWidget_Equipment* _pWidget);

	void Open();
	void Close();

	bool OnEquip(AItem_Equipment* _pEquipment);

	/* Get */
	FORCEINLINE const FEquipmentSlot_Info& GetWeaponSlot()          const { return m_WeaponSlot; }
	FORCEINLINE const FEquipmentSlot_Info& GetSecondaryWeaponSlot() const { return m_SecondaryWeaponSlot; }
	FORCEINLINE const FEquipmentSlot_Info& GetNecklaceSlot()        const { return m_NecklaceSlot; }
	FORCEINLINE const FEquipmentSlot_Info& GetBeltSlot()            const { return m_BeltSlot; }
	
	FORCEINLINE const TArray<FEquipmentSlot_Info>& GetRingSlots()    const { return m_RingSlots; }
	FORCEINLINE const TArray<FEquipmentSlot_Info>& GetEarringSlots() const { return m_EarringSlots; }

	FORCEINLINE const bool& GetIsOpen() const { return m_bIsOpen; }

private :
	bool _EquipWeapon(AItem_Equipment* _pEquipment);
	bool _EquipSecondaryWeapon(AItem_Equipment* _pEquipment);
	bool _EquipNecklace(AItem_Equipment* _pEquipment);
	bool _EquipBelt(AItem_Equipment* _pEquipment);
	bool _EquipRing(AItem_Equipment* _pEquipment);
	bool _EquipEarring(AItem_Equipment* _pEquipment);

	bool _UnEquipWeapon();
	bool _UnEquipSecondaryWeapon();
	bool _UnEquipNecklace();
	bool _UnEquipBelt();
	bool _UnEquipRing();
	bool _UnEquipEarring();

	bool _EquipRing_L(AItem_Equipment* _pEquipment);
	bool _UnEquipRing_L();

	bool _EquipRing_R(AItem_Equipment* _pEquipment);
	bool _UnEquipRing_R();

	bool _EquipEarring_L(AItem_Equipment* _pEquipment);
	bool _UnEquipEarring_L();

	bool _EquipEarring_R(AItem_Equipment* _pEquipment);
	bool _UnEquipEarring_R();

	void _UpdatePlayerStats(AItem_Equipment* _pEquipment, bool _bIsPositive);
};
