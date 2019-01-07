// Fill out your copyright notice in the Description page of Project Settings.

#include "Chest.h"
#include "Components/Component_Pickup.h"
#include "Widgets/Widget_Main.h"
#include "Widgets/Pickup/Widget_Pickup.h"
#include "Players/Player_Character.h"
#include "Items/Item_Base.h"

#include <Components/SphereComponent.h>
#include <Components/ArrowComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <UObject/ConstructorHelpers.h>

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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Chest(TEXT("StaticMesh'/Game/03_Resources/Meshes/Chest/SM_Chest.SM_Chest'"));
	if (SM_Chest.Succeeded())
	{
		m_pMesh->SetStaticMesh(SM_Chest.Object);
	}
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();

}

void AChest::OnInteract(APlayer_Character* _pUser)
{
	if (_pUser->GetTarget() && _pUser->GetTarget() != this)
	{
		Cast<IInterface_Interaction>(_pUser->GetTarget())->UnInteract();
	}

	if (!m_pPickup->GetIsOpen())
	{
		SetInteractionUser(_pUser);

		if (GetInteractionUser()->GetTarget() && (GetInteractionUser()->GetTarget() != this))
		{
			if (IInterface_Interaction* pInteraction = Cast<IInterface_Interaction>(GetInteractionUser()->GetTarget()))
			{
				pInteraction->UnInteract();
				GetInteractionUser()->SetTarget(nullptr);
			}
		}
		GetInteractionUser()->SetTarget(this);
		UWidget_Base* pWidget = GetInteractionUser()->GetMainWidget()->GetPickupWidget();
		m_pPickup->InitComponent(pWidget);
		m_pPickup->Open();
	}
}

void AChest::UnInteract()
{
	if (m_pPickup->GetIsOpen())
	{
		GetInteractionUser()->SetTarget(nullptr);
		SetInteractionUser(nullptr);
		m_pPickup->Close();
	}
}

void AChest::AddItemClasses(const TMap<TSubclassOf<AItem_Base>, int>& _ItemClassList)
{
	for (auto& ItemClass : _ItemClassList)
	{
		m_pPickup->AddItemClass(ItemClass.Key, ItemClass.Value);
	}
}

