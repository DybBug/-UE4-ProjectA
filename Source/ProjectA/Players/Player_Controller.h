// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player_Controller.generated.h"

/**
 * 
 */
class APlayer_Character;
class UComponent_Base;

UCLASS()
class PROJECTA_API APlayer_Controller : public APlayerController
{
	GENERATED_BODY()

public :
	APlayer_Controller();
	
protected :
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private :
	APlayer_Character* m_pPlayer;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	bool m_bIsLookAround;

	// #. 둘러보기 최대 각도.(기본 : 120)
	UPROPERTY(EditAnywhere, Category = "Configuration")
	float m_MaxAngleOfLookAround = 120.f;

private :
	//
	// #. Input Action Functions.
	//
	UFUNCTION()
	void _Toggle_LookAround();

	UFUNCTION()
	void _Toggle_ShowMouseCursor();

	UFUNCTION()
	void _Inventory_OpenAndClose();

	UFUNCTION()
	void _Equipment_OpenAndClose();

	UFUNCTION()
	void _Stat_OpenAndClose();

	UFUNCTION()
	void _Crafting_OpenAndClose();

	UFUNCTION()
	void _SkillTree_OpenAndClose();

	UFUNCTION()
	void _Interact();

	UFUNCTION()
	void _Jump();

	UFUNCTION()
	void _Attack();

	UFUNCTION()
	void _AnyKey();

	//
	// #. Input Axis Functions.
	//
	UFUNCTION()
	void _MoveForward(float _Value);

	UFUNCTION()
	void _MoveRight(float _Value);
	
	UFUNCTION()
	void _LookUp(float _Value);

	UFUNCTION()
	void _Turn(float _Value);
	
};
