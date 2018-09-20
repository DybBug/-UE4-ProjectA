// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_Controller.h"
#include "Player_Character.h"
#include "Enemies/Enemy_Base.h"
#include "Interfaces/Interface_Interaction.h"

#include <WidgetBlueprintLibrary.h>
#include <Camera/CameraComponent.h>

APlayer_Controller::APlayer_Controller()
{

}

void APlayer_Controller::BeginPlay()
{
	Super::BeginPlay();

	m_pPlayer = Cast<APlayer_Character>(GetPawn());
	InputYawScale = 1.f;
	InputPitchScale = 1.f;
}

void APlayer_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Toggle_LookAround"), IE_Pressed, this, &APlayer_Controller::_Toggle_LookAround);
	InputComponent->BindAction(TEXT("Toggle_LookAround"), IE_Released, this, &APlayer_Controller::_Toggle_LookAround);
	InputComponent->BindAction(TEXT("Toggle_ShowMouseCursor"), IE_Released, this, &APlayer_Controller::_Toggle_ShowMouseCursor);
	InputComponent->BindAction(TEXT("Inventory_OpenAndClose"), IE_Pressed, this, &APlayer_Controller::_Inventory_OpenAndClose);
	InputComponent->BindAction(TEXT("Equipment_OpenAndClose"), IE_Pressed, this, &APlayer_Controller::_Equipment_OpenAndClose);
	InputComponent->BindAction(TEXT("Stat_OpenAndClose"), IE_Pressed, this, &APlayer_Controller::_Stat_OpenAndClose);
	InputComponent->BindAction(TEXT("Crafting_OpenAndClose"), IE_Pressed, this, &APlayer_Controller::_Crafting_OpenAndClose);
	InputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayer_Controller::_Interact);
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayer_Controller::_Jump);
	InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &APlayer_Controller::_Attack);

	InputComponent->BindAxis(TEXT("MoveForward"), this, &APlayer_Controller::_MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &APlayer_Controller::_MoveRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &APlayer_Controller::_LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &APlayer_Controller::_Turn);
}

void APlayer_Controller::_Toggle_LookAround()
{
	m_bIsLookAround = !m_bIsLookAround;
	if (m_bIsLookAround)
	{
		m_pPlayer->bUseControllerRotationYaw = false;
	}
	else
	{
		m_pPlayer->bUseControllerRotationYaw = true;
		SetControlRotation(m_pPlayer->GetActorRotation());
	}
}

void APlayer_Controller::_Toggle_ShowMouseCursor()
{
	bShowMouseCursor = !bShowMouseCursor;
	if (bShowMouseCursor)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this);
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	}
}

void APlayer_Controller::_Inventory_OpenAndClose()
{
	m_pPlayer->InventoryOpenAndClose();
}

void APlayer_Controller::_Equipment_OpenAndClose()
{
	m_pPlayer->EquipmentOpenAndClose();
}

void APlayer_Controller::_Stat_OpenAndClose()
{
	m_pPlayer->StatOpenAndClose();
}

void APlayer_Controller::_Crafting_OpenAndClose()
{
	m_pPlayer->CraftingOpenAndClose();
}

void APlayer_Controller::_Interact()
{
	FHitResult Result;
	FVector Direction = m_pPlayer->GetCamera()->GetForwardVector();
	FVector Start = m_pPlayer->GetCamera()->GetComponentLocation();
	FVector End = Start + (Direction * 1500.f);

	if (GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECollisionChannel::ECC_Visibility))
	{
		// #. 상호작용이 가능한 액터일 경우.
		if (IInterface_Interaction* pInteract = Cast<IInterface_Interaction>(Result.GetActor()))
		{
			pInteract->GetPlayer() ? pInteract->UnInteract() : pInteract->OnInteract(m_pPlayer);
			return;
		}	
	}

	if (m_pPlayer->GetTarget())
	{
		IInterface_Interaction* pInteract = Cast<IInterface_Interaction>(m_pPlayer->GetTarget());
		pInteract->UnInteract();
		return;
	}
}

void APlayer_Controller::_Jump()
{
	m_pPlayer->Jump();
}

void APlayer_Controller::_Attack()
{
	if (m_pPlayer->GetIsLockOn())
	{
		m_pPlayer->Attack();
	}
}

void APlayer_Controller::_MoveForward(float _Value)
{
	if ((_Value != 0.f) && m_pPlayer)
	{
		m_pPlayer->MoveForward(_Value);
	}
}

void APlayer_Controller::_MoveRight(float _Value)
{
	if ((_Value != 0.f) && m_pPlayer)
	{
		m_pPlayer->MoveRight(_Value);
	}
}

void APlayer_Controller::_LookUp(float _Value)
{
	if (_Value != 0.f)
	{
		FRotator CurrControlRot = GetControlRotation();
		_Value = FMath::ClampAngle(CurrControlRot.Pitch + _Value, -40.f, 40.f);
		_Value -= CurrControlRot.Pitch;
		AddPitchInput(_Value);
		return;
	}
}

void APlayer_Controller::_Turn(float _Value)
{
	if (_Value != 0.f)
	{
		if (m_bIsLookAround)
		{
			FRotator CurrControlRot = GetControlRotation();

			CurrControlRot.Yaw = FMath::ClampAngle(
				                 CurrControlRot.Yaw + _Value,
				                 m_pPlayer->GetActorRotation().Yaw - m_MaxAngleOfLookAround,
				                 m_pPlayer->GetActorRotation().Yaw + m_MaxAngleOfLookAround);

			SetControlRotation(CurrControlRot);
			return;
		}
		else
		{
			AddYawInput(_Value);
			return;
		}
	}
}
