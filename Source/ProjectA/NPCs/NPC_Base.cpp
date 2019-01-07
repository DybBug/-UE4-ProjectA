// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_Base.h"
#include"ProjectA.h"

#include <Components/ArrowComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/CapsuleComponent.h>
#include <Engine.h>


// Sets default values
ANPC_Base::ANPC_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = m_pArrow;

	m_pCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	m_pCollision->SetCollisionObjectType(UEngineTypes::ConvertToCollisionChannel(OTQ_NPC));
	m_pCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_pCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	m_pCollision->SetupAttachment(RootComponent);

	m_pMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ANPC_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPC_Base::Tick(float DeltaSeconds)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("NPC_Tick"));
}

