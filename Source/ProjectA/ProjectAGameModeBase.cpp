// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectAGameModeBase.h"
#include "Players/Player_Character.h"
#include "Players/Player_Controller.h"

#include <UObject/ConstructorHelpers.h>
#include <Engine/World.h>
#include <Engine/LevelStreaming.h>

AProjectAGameModeBase::AProjectAGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APlayer_Character> BP_Player_Character(TEXT("Blueprint'/Game/01_Blueprints/Player/BP_Player_Character.BP_Player_Character_C'"));
	if (BP_Player_Character.Succeeded())
	{
		DefaultPawnClass = BP_Player_Character.Class;
	}
	PlayerControllerClass = APlayer_Controller::StaticClass();
}

void AProjectAGameModeBase::StartPlay()
{
	Super::StartPlay();
}
