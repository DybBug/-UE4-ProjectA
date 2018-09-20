// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_Character.h"
#include "Widgets/Widget_Main.h"
#include "Widgets/Misc/Widget_StatBar.h"
#include "Components/Component_Inventory.h"
#include "Components/Component_Equipment.h"
#include "Components/Component_Stat.h"
#include "Components/Component_Crafting.h"
#include "Components/Component_Skill.h"
#include "Items/Item_Equipment.h"

#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/PlayerController.h>
#include <Camera/CameraComponent.h>
#include <TimerManager.h>
#include <Engine.h>

// Sets default values
APlayer_Character::APlayer_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionObjectType(UEngineTypes::ConvertToCollisionChannel(OTQ_Player));
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(UEngineTypes::ConvertToCollisionChannel(OTQ_Equipment), ECollisionResponse::ECR_Ignore);

	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_pSpringArm->bUsePawnControlRotation = true;
	m_pSpringArm->bInheritPitch = true;
	m_pSpringArm->bInheritYaw = true;
	m_pSpringArm->bInheritRoll = false;
	m_pSpringArm->SetupAttachment(RootComponent);

	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_pCamera->SetupAttachment(m_pSpringArm);

	m_pInventory = CreateDefaultSubobject<UComponent_Inventory>(TEXT("Inventory"));
	m_pEquipment = CreateDefaultSubobject<UComponent_Equipment>(TEXT("Equipment"));
	m_pStat      = CreateDefaultSubobject<UComponent_Stat>(TEXT("Stat"));
	m_pCrafting  = CreateDefaultSubobject<UComponent_Crafting>(TEXT("Crafting"));
	m_pSkill     = CreateDefaultSubobject<UComponent_Skill>(TEXT("Skill"));
}

// Called when the game starts or when spawned
void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_MainWidgetClass))
	{
		m_pMainWidget = CreateWidget<UWidget_Main>(GetWorld(), m_MainWidgetClass);
		bool bSuccess = m_pMainWidget->InitWidget(this);

		if (bSuccess)
		{
			m_pInventory->InitComponent(m_pMainWidget->GetInventoryWidget());
			m_pEquipment->InitComponent(m_pMainWidget->GetEquipmentWidget());
			m_pStat->InitComponent(m_pMainWidget->GetStatWidget());
			m_pCrafting->InitComponent(m_pMainWidget->GetCraftingWidget());
	
			m_pMainWidget->AddToViewport();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Create Main Widget Failed."));
		}
	}
}

// Called every frame
void APlayer_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayer_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindKey(EKeys::Hyphen, IE_Pressed, this, &APlayer_Character::_DecreaseHealth);

}

void APlayer_Character::MoveForward(float _Value)
{
	AddMovementInput(GetActorForwardVector(), _Value);

}

void APlayer_Character::MoveRight(float _Value)
{
	AddMovementInput(GetActorRightVector(), _Value);
}

void APlayer_Character::Attack()
{
	if (m_pEquipment->GetWeaponSlot().pItem)
	{
		m_pSkill->UseSkill();
	}
}

void APlayer_Character::LockOn(AActor* _pTarget)
{
	if (m_pTarget != _pTarget)
	{
		m_pTarget = _pTarget;
		m_bIsLockOn = true;

		GetWorld()->GetTimerManager().SetTimer(m_hLockOnTimer, this, &APlayer_Character::_LookAtTarget, 0.005f, true);

		GetWorld()->GetFirstPlayerController()->InputYawScale = 0.f;
		GetWorld()->GetFirstPlayerController()->InputPitchScale = 0.f;

		m_pSpringArm->bInheritPitch = false;
		m_pCamera->bUsePawnControlRotation = true;

		m_TempCameraRot = m_pCamera->GetRelativeTransform().GetRotation().Rotator();
		UE_LOG(LogClass, Warning, TEXT("%f, %f, %f"), m_TempCameraRot.Pitch, m_TempCameraRot.Yaw, m_TempCameraRot.Roll);
	}
}

void APlayer_Character::LockOff()
{
	if (m_pTarget)
	{
		m_pTarget = nullptr;
		m_bIsLockOn = false;

		GetWorld()->GetTimerManager().ClearTimer(m_hLockOnTimer);

		GetWorld()->GetFirstPlayerController()->InputYawScale = 1.f;
		GetWorld()->GetFirstPlayerController()->InputPitchScale = 1.f;

		m_pSpringArm->bInheritPitch = true;
		m_pCamera->bUsePawnControlRotation = false;

		m_pCamera->SetRelativeRotation(m_TempCameraRot);
	}
}

void APlayer_Character::InventoryOpenAndClose()
{
	if (m_pInventory->GetIsOpen())
	{
		m_pInventory->Close();
	}
	else
	{
		m_pInventory->Open();
	}
}

void APlayer_Character::EquipmentOpenAndClose()
{
	if (m_pEquipment->GetIsOpen())
	{
		m_pEquipment->Close();
	}
	else
	{
		m_pEquipment->Open();
	}
}

void APlayer_Character::StatOpenAndClose()
{
	if (m_pStat->GetIsOpen())
	{
		m_pStat->Close();
	}
	else
	{
		m_pStat->Open();
	}
}

void APlayer_Character::CraftingOpenAndClose()
{
	if (m_pCrafting->GetIsOpen())
	{
		m_pCrafting->Close();
	}
	else
	{
		m_pCrafting->Open();
	}
}

FVector2D APlayer_Character::GetMovementDirection()
{
	FVector Forward     = GetActorForwardVector();
	FVector Right       = GetActorRightVector();
	FVector VelocityDir = GetVelocity().GetSafeNormal();

	float X = FVector::DotProduct(Forward, VelocityDir);
	float Y =FVector::DotProduct(Right, VelocityDir);

	return FVector2D(X, Y);
}

bool APlayer_Character::ModifyMaxStat(EStat_Types _Type, float _Value)
{
	FStat_Info Stat = m_pStat->GetStat(_Type);

	if (_Value < 0.f && Stat.MaxValue > 0)
	{
		m_pStat->ModifyMaxValueByType(_Type, _Value);
		return true;
	}
	else
	{
		m_pStat->ModifyMaxValueByType(_Type, _Value);
		return true;
	}
	return false;
}

bool APlayer_Character::ModifyCurrentStat(EStat_Types _Type, float _Value)
{
	FStat_Info Stat = m_pStat->GetStat(_Type);

	if (_Value > 0.f)
	{
		if (Stat.MaxValue != 0)
		{
			if (Stat.CurrentValue < Stat.MaxValue)
			{
				m_pStat->ModifyCurrentValueByType(_Type, _Value);
				return true;
			}
		}
		else
		{
			m_pStat->ModifyCurrentValueByType(_Type, _Value);
			return true;
		}
	}
	else if (_Value < 0.f)
	{
		if (Stat.CurrentValue > 0)
		{
			m_pStat->ModifyCurrentValueByType(_Type, _Value);
			return true;
		}
	}
	return false;
}

bool APlayer_Character::ModifyStat(EStat_Types _Type, float _Value)
{
	FStat_Info Stat = m_pStat->GetStat(_Type);
	if (Stat.MaxValue == 0)
	{
		ModifyCurrentStat(_Type, _Value);
		return true;
	}
	else
	{
		ModifyMaxStat(_Type, _Value);
		return true;
	}
	return false;
}

void APlayer_Character::LevelUp()
{
	for (auto Stat : m_pStat->GetStats())
	{
		if (Stat.Value.MaxValue > 0.f)
		{
			m_pStat->ModifyMaxValueByType(Stat.Key, Stat.Value.IncreasePerLevelUp);
			m_pStat->ModifyCurrentValueByType(Stat.Key, Stat.Value.IncreasePerLevelUp);

			if (Stat.Key == EStat_Types::Experience)
			{
				m_pStat->ModifyCurrentValueByType(Stat.Key, -(Stat.Value.MaxValue + Stat.Value.IncreasePerLevelUp));
			}
		}
		else
		{
			m_pStat->ModifyCurrentValueByType(Stat.Key, Stat.Value.IncreasePerLevelUp);
		}
	}
	m_pStat->ModifyStatPoint(5);
}

bool APlayer_Character::GainExperience(float _Value)
{
	bool bSuccess = ModifyCurrentStat(EStat_Types::Experience, _Value);

	FStat_Info ExpInfo = m_pStat->GetStat(EStat_Types::Experience);
	if (ExpInfo.CurrentValue >= ExpInfo.MaxValue)
	{
		LevelUp();
	}

	return bSuccess;
}

void APlayer_Character::_DecreaseHealth()
{
	ModifyCurrentStat(EStat_Types::Experience, 10.f);

	FStat_Info ExpInfo = m_pStat->GetStat(EStat_Types::Experience);
	if (ExpInfo.CurrentValue >= ExpInfo.MaxValue)
	{
		LevelUp();
	}	
}

void APlayer_Character::_LookAtTarget()
{
	FVector CameraLocation = m_pCamera->GetComponentLocation();
	FVector TargetLocation = m_pTarget->GetActorLocation();

	FVector Direction = (TargetLocation - CameraLocation);

	float YawAngle = FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X));
	float PitchAngle = GetControlRotation().Pitch;

	if (Direction.Size() != 0.f)
	{
		PitchAngle = FMath::RadiansToDegrees(FMath::Asin(Direction.Z / Direction.Size()));
	}

	FRotator ControlRot = GetControlRotation();

	ControlRot.Yaw = YawAngle;
	ControlRot.Pitch = PitchAngle;
	GetController()->SetControlRotation(ControlRot);
}

