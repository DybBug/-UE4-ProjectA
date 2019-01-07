// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

class UBoxComponent;
class AEnemy_Base;

UCLASS()
class PROJECTA_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	bool Spawn(AEnemy_Base* _Enemy = nullptr);

private :
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* m_pSpawnVolume;

	// #. 스폰할 적 클래스.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<AEnemy_Base> m_SpawnEnemyClass;

	// #. 최대 스폰 갯수.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	uint8 m_MaxSpawnCount;

	// #. 스폰 시간.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	uint8 m_SpawnTime;

	// #. 적군 목록.
	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TArray<AEnemy_Base*> m_SpawnEnemyList;

};
