// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelStreamingActor.h"
#include "ProjectAGameModeBase.h"

#include <GameFramework/Character.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/LevelStreaming.h>


TMap<FName, int> ALevelStreamingActor::m_AllStreamLevels;

// Sets default values
ALevelStreamingActor::ALevelStreamingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pStreamingVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("StreamingVolume"));
	m_pStreamingVolume->OnComponentBeginOverlap.AddDynamic(this, &ALevelStreamingActor::_BeginOverlap);
	m_pStreamingVolume->OnComponentEndOverlap.AddDynamic(this, &ALevelStreamingActor::_EndOverlap);
	RootComponent = m_pStreamingVolume;

	m_StreamLevelIndex = 0;
}

// Called when the game starts or when spawned
void ALevelStreamingActor::BeginPlay()
{
	Super::BeginPlay();

	_LoadAllStreamLevels();

	m_pPlayer = UGameplayStatics::GetPlayerCharacter(this, 0);
	if(m_pPlayer)
	{
		if (m_pStreamingVolume->IsOverlappingActor(m_pPlayer))
		{
			_LoadStreamLevel();
		}
	}	
}

void ALevelStreamingActor::_BeginOverlap(
	UPrimitiveComponent* _pOverlappedComponent,
	AActor* _pOtherActor,
	UPrimitiveComponent* _pOtherComp,
	int32 _OtherBodyIndex,
	bool _bFromSweep,
	const FHitResult& _SweepResult)
{
	if (_pOtherActor == m_pPlayer)
	{
		_LoadStreamLevel();
	}
}

void ALevelStreamingActor::_LoadStreamLevel()
{
	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.ExecutionFunction = "_LoadComplete";
	LatentAction.Linkage = 1;
	LatentAction.UUID = GetUniqueID();

	if (m_AllStreamLevels[m_LevelNames[m_StreamLevelIndex]] == 0)
	{
		UGameplayStatics::LoadStreamLevel(this, m_LevelNames[m_StreamLevelIndex], true, true, LatentAction);
	}
	else if (m_AllStreamLevels[m_LevelNames[m_StreamLevelIndex]] > 0)
	{
		_LoadComplete();
	}	
}

void ALevelStreamingActor::_LoadComplete()
{
	m_AllStreamLevels[m_LevelNames[m_StreamLevelIndex]]++;

	if (m_StreamLevelIndex < m_LevelNames.Num()-1)
	{
		m_StreamLevelIndex++;
		_LoadStreamLevel();
	}
}

void ALevelStreamingActor::_EndOverlap(
	UPrimitiveComponent* _pOverlappedComponent,
	AActor* _pOtherActor,
	UPrimitiveComponent* _pOtherComp,
	int32 _OtherBodyIndex)
{
	if (_pOtherActor == m_pPlayer)
	{
		_UnloadStreamLevel();
	}
}

void ALevelStreamingActor::_UnloadStreamLevel()
{
	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.ExecutionFunction = "_UnloadComplete";
	LatentAction.Linkage = 1;
	LatentAction.UUID = GetUniqueID();	

	if (m_AllStreamLevels[m_LevelNames[m_StreamLevelIndex]] == 1)
	{
		UGameplayStatics::UnloadStreamLevel(this, m_LevelNames[m_StreamLevelIndex], LatentAction, false);
	}
	else if (m_AllStreamLevels[m_LevelNames[m_StreamLevelIndex]] > 0)
	{
		_UnloadComplete();
	}
}

void ALevelStreamingActor::_UnloadComplete()
{
	m_AllStreamLevels[m_LevelNames[m_StreamLevelIndex]]--;

	if (m_StreamLevelIndex > 0)
	{
		m_StreamLevelIndex--;
		_UnloadStreamLevel();
	}
}

void ALevelStreamingActor::_LoadAllStreamLevels()
{
	TArray<ULevelStreaming*> LevelStreamings = GetWorld()->GetStreamingLevels();
	for (auto& Element : LevelStreamings)
	{
		FString Name = Element->GetWorldAssetPackageName();

		int Index;
		Name.FindLastChar('_', Index);
		Name.RemoveAt(0, Index + 1);

		if (!m_AllStreamLevels.Contains(*Name))
		{
			m_AllStreamLevels.Add(*Name, 0);
		}
		else
		{
			m_AllStreamLevels[*Name] = 0;
		}
	}
}


