// Fill out your copyright notice in the Description page of Project Settings.

#include "Chest.h"
#include "Components/Component_Pickup.h"
#include "Widgets/Widget_Main.h"
#include "Players/Player_Character.h"

#include <Components/SphereComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>


// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	m_pCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_pCollision->SetCollisionObjectType(ECC_WorldStatic);
	m_pCollision->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	RootComponent = m_pCollision;

	m_pArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	m_pArrow->SetupAttachment(RootComponent);

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetupAttachment(RootComponent);

	m_pPickup = CreateDefaultSubobject<UComponent_Pickup>(TEXT("Pickup"));

}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();

}

void AChest::OnInteract(APlayer_Character* _pPlayer)
{
	if (!m_pPickup->GetIsOpen())
	{
		m_pPlayer = _pPlayer;
		m_bBeInteracting = true;

		if (m_pPlayer->GetTarget() && (m_pPlayer->GetTarget() != this))
		{
			if (IInterface_Interaction* pInteraction = Cast<IInterface_Interaction>(m_pPlayer->GetTarget()))
			{
				pInteraction->UnInteract();
				m_pPlayer->SetTarget(nullptr);
			}
		}
		m_pPlayer->SetTarget(this);
		m_pPickup->Open(_pPlayer->GetMainWidget()->GetPickupWidget());
	}
}

void AChest::UnInteract()
{
	if (m_pPickup->GetIsOpen())
	{
		m_bBeInteracting = false;
		m_pPlayer->SetTarget(nullptr);
		m_pPlayer = nullptr;
		m_pPickup->Close();
	}
}

