// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnActor.h"
#include "Enemies/Enemy_Base.h"

#include <Components/BoxComponent.h>
#include <Components/CapsuleComponent.h>
#include <TimerManager.h>
#include <Kismet/KismetMathLibrary.h>
#include <NavigationSystem.h>
#include <Engine/LevelScriptActor.h>

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pSpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = m_pSpawnVolume;
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();	
	for (int i = 0; i < m_MaxSpawnCount; ++i)
	{
		FVector SpawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), m_pSpawnVolume->GetScaledBoxExtent());
		FActorSpawnParameters Params;
		Params.OverrideLevel = GetLevel();
		AEnemy_Base* pEnemy = GetWorld()->SpawnActor<AEnemy_Base>(m_SpawnEnemyClass, SpawnLoc, FRotator::ZeroRotator, Params);
		pEnemy->InitEnemy(SpawnLoc, this, i);
		m_SpawnEnemyList.Add(pEnemy);
	}	
}

bool ASpawnActor::Spawn(AEnemy_Base* _pEnemy)
{
	if (_pEnemy)
	{
		if (m_SpawnEnemyList.Contains(_pEnemy))
		{
			FTimerHandle hTimer;

			int Index = _pEnemy->GetID();
			GetWorld()->GetTimerManager().SetTimer(hTimer, [&, Index]{
				FVector SpawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), m_pSpawnVolume->GetScaledBoxExtent());
				m_SpawnEnemyList[Index]->InitEnemy(SpawnLoc, this, Index);
				
				GetWorld()->GetTimerManager().ClearTimer(hTimer);
			}, m_SpawnTime, false);
		}
	}
	return false;
}

