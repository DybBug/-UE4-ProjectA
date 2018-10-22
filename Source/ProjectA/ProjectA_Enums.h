// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "ProjectA_Enums.generated.h"

#define CONVERT_DISPLAYNAME_TO_STRING(eType, eValue) ( (FindObject<UEnum>(ANY_PACKAGE, eType, true) != nullptr) ? (FindObject<UEnum>(ANY_PACKAGE, eType, true)->GetDisplayNameTextByIndex((int8)eValue)).ToString() : FString("Convert Failed!") );

UENUM(BlueprintType)
enum class EItem_Types : uint8
{
	None        UMETA(DisplayName = "없음"),
	Consumables UMETA(DisplayName = "소모품"),
	Equipment   UMETA(DisplayName = "장비"),
	Material    UMETA(DisplayName =  "재료"),
	Misc        UMETA(DisplayName = "잡화"),
	Max
};

UENUM(BlueprintType)
enum class EStat_Types : uint8
{
	Level      UMETA(DisplayName = "레벨"),
	Experience UMETA(DisplayName = "경험치"),
	Health     UMETA(DisplayName = "생명력"),
	Mana       UMETA(DisplayName = "마나"),
	Stamina    UMETA(DisplayName = "스테미나"),
	Attack     UMETA(DisplayName = "공격력"),
	Defensive  UMETA(DisplayName = "방어력"),
	Max
};

UENUM(BlueprintType)
enum class EEquipment_Types : uint8
{
	None            UMETA(DisplayName = "알 수 없음"),
	Weapon          UMETA(DisplayName = "무기"),
	SecondaryWeapon UMETA(DisplayName = "보조 무기"),
	Necklace        UMETA(DisplayName = "목걸이"),
	Belt            UMETA(DisplayName = "벨트"),
	Ring            UMETA(DisplayName = "반지"),
	Earring         UMETA(DisplayName = "귀걸이"),
	Max
};

UENUM(BlueprintType)
enum class EQuest_Categories : uint8
{
	Main_Quest UMETA(DisplayName = "메인 퀘스트"),
	Sub_Quest  UMETA(DisplayName = "서브 퀘스트"),
	Event      UMETA(DisplayName = "이벤트"),
	Max
};

UENUM(BlueprintType)
enum class EGoal_Types : uint8
{
	Hunt    UMETA(DisplayName = "사냥"),
	Collect UMETA(DisplayName = "수집"),
	Talk    UMETA(DisplayName = "대화"),
	Explore UMETA(DisplayName = "탐사"),
	Max
};
