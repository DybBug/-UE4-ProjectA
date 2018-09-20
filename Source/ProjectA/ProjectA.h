// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ProjectA.generated.h"

enum EObjectTypeQuery;
enum ETraceTypeQuery;

const EObjectTypeQuery OTQ_Player = EObjectTypeQuery::ObjectTypeQuery1;
const EObjectTypeQuery OTQ_Enemy = EObjectTypeQuery::ObjectTypeQuery2;
const EObjectTypeQuery OTQ_Equipment = EObjectTypeQuery::ObjectTypeQuery3;
const EObjectTypeQuery OTQ_NPC = EObjectTypeQuery::ObjectTypeQuery4;

USTRUCT(BlueprintType)
struct FTemp
{
	GENERATED_BODY()
};
