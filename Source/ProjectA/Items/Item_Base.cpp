// Fill out your copyright notice in the Description page of Project Settings.

#include "Item_Base.h"
#include "Players/Player_Character.h"


// Sets default values
AItem_Base::AItem_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pPlayer = nullptr;

}

// Called when the game starts or when spawned
void AItem_Base::BeginPlay()
{
	Super::BeginPlay();	
}

void AItem_Base::InitItem(AActor* _pOwner)
{
	m_pPlayer = Cast<APlayer_Character>(_pOwner);
	SetActorHiddenInGame(true);
}


