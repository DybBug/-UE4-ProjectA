// Fill out your copyright notice in the Description page of Project Settings.

#include "Skill_Base.h"


// Sets default values
ASkill_Base::ASkill_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASkill_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

