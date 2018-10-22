// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectA_Enums.h"
#include "Component_Quest.generated.h"

//
// #. 보상정보.
//
USTRUCT(BlueprintType)
struct FReward_Info
{
	GENERATED_BODY()

public :
	// #. 경험치.
	UPROPERTY(EditAnywhere, Category = "Reward_Info")
	float Experience;

	// #. 아이템 및 수량.
	UPROPERTY(EditAnywhere, Category = "Reward_Info")
	TMap<TSubclassOf<class AItem_Base>, int> ItemClass;
};

//
// #. 목표 정보.
//
USTRUCT(BlueprintType)
struct FGoal_Info
{
	GENERATED_BODY()

public :
	// #. 목표 유형.
	UPROPERTY(EditAnywhere, Category = "Goal_Info")
	EGoal_Types Type;

	// #. 설명.
	UPROPERTY(EditAnywhere, Category = "Goal_Info")
	FText Description;

	// #. 목표 객체 클래스.
	UPROPERTY(EditAnywhere, Category = "Goal_Info")
	TSubclassOf<AActor> GoalClass;

	// #. 목표 횟수.
	UPROPERTY(EditAnywhere, Category = "Goal_Info")
	int GoalAmount;

	// #. 위치.
	UPROPERTY(EditAnywhere, Category = "Goal_Info")
	FVector Location;

	// #. 탐사 반경.
	UPROPERTY(EditAnywhere, Category = "Goal_Info")
	float ExplorationRadius;

	// #. 성공 여부.
	UPROPERTY(EditAnywhere, Category = "Goal_Info")
	bool bIsSuccess;
};

//
// #. 퀘스트 정보.
//
USTRUCT(BlueprintType)
struct FQuest_Info
{
	GENERATED_BODY()

public :
	// #. 카테고리.
	UPROPERTY(EditAnywhere, Category = "Quest_Info")
	EQuest_Categories Category;

	// #. 적정 레벨.
	UPROPERTY(EditAnywhere, Category = "Quest_Info")
	float AppropriateLevel;

	// #. 제목.
	UPROPERTY(EditAnywhere, Category = "Quest_Info")
	FName Title;

	// #. 설명.
	UPROPERTY(EditAnywhere, Category = "Quest_Info")
	FText Description;

	// #. 목표 목록.
	UPROPERTY(EditAnywhere, Category = "Quest_Info")
	TArray<FGoal_Info> GoalInfos;

	// #. 보상.
	UPROPERTY(EditAnywhere, Category = "Quest_Info")
	FReward_Info Reward_Info; 	

	// #. 완료 여부.
	UPROPERTY(EditAnywhere, Category = "Quest_Info")
	bool bIsComplete;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Quest : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Quest();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private :


	
};
