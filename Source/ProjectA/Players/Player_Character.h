// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectA.h"
#include "Player_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidget_Main;
class UComponent_Inventory;
class UComponent_Equipment;
class UComponent_Stat;
class UComponent_Crafting;

enum class EStat_Types :uint8;

UCLASS()
class PROJECTA_API APlayer_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected :
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* m_pSpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* m_pCamera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UComponent_Inventory* m_pInventory;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UComponent_Equipment* m_pEquipment;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UComponent_Stat* m_pStat;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UComponent_Crafting* m_pCrafting;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_Main> m_MainWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	AActor* m_pTarget;

	UWidget_Main* m_pMainWidget;

public :
	void MoveForward(float _Value);
	void MoveRight(float _Value);

	void InventoryOpenAndClose();
	void EquipmentOpenAndClose();
	void StatOpenAndClose();
	void CraftingOpenAndClose();

	UFUNCTION(BlueprintPure)
	FVector2D GetMovementDirection();

	bool ModifyMaxStat(EStat_Types Type, float _Value);
	bool ModifyCurrentStat(EStat_Types _Type, float _Value);
	bool ModifyStat(EStat_Types _Type, float _Value);
	void LevelUp();
	bool GainExperience(float _Value);

	/* Get */
	FORCEINLINE UCameraComponent* const& GetCamera() const { return m_pCamera; }

	FORCEINLINE UComponent_Inventory* const& GetInventory()  const { return m_pInventory; }
	FORCEINLINE UComponent_Equipment* const& GetEquipment()  const { return m_pEquipment; }
	FORCEINLINE UComponent_Stat*      const& GetStat()       const { return m_pStat; }
	FORCEINLINE UComponent_Crafting*  const& GetCrafting()   const { return m_pCrafting; }
	FORCEINLINE UWidget_Main*         const& GetMainWidget() const { return m_pMainWidget; }
	FORCEINLINE AActor*               const& GetTarget()     const { return m_pTarget; }

	/* Set */
	FORCEINLINE void SetTarget(AActor* _pTarget) { m_pTarget = _pTarget; }


private :
	UFUNCTION()
	void _DecreaseHealth();
	
};
