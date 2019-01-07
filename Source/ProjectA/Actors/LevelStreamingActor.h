// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStreamingActor.generated.h"

class UBoxComponent;
class AProjectAGameModeBase;

UCLASS()
class PROJECTA_API ALevelStreamingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelStreamingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private :
	static TMap<FName, int> m_AllStreamLevels;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	UBoxComponent* m_pStreamingVolume;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TArray<FName> m_LevelNames;

	UPROPERTY()
	AActor* m_pPlayer;

	int m_StreamLevelIndex;

protected :
	UFUNCTION()
	void _BeginOverlap(UPrimitiveComponent* _pOverlappedComponent, AActor* _pOtherActor, UPrimitiveComponent* _pOtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);

	void _LoadStreamLevel();

	UFUNCTION()
	void _LoadComplete();

	UFUNCTION()
	void _EndOverlap(UPrimitiveComponent* _pOverlappedComponent, AActor* _pOtherActor, UPrimitiveComponent* _pOtherComp, int32 _OtherBodyIndex);

	void _UnloadStreamLevel();

	UFUNCTION()
	void _UnloadComplete();

	void _LoadAllStreamLevels();
};
