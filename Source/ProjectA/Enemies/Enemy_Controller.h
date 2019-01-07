// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_Controller.generated.h"

class AEnemy_Base;
enum class EEnemy_States : uint8;
/**
 * 
 */

UCLASS()
class PROJECTA_API AEnemy_Controller : public AAIController
{
	GENERATED_BODY()

public :
	AEnemy_Controller();
	virtual void Possess(APawn* InPawn) override;

	void SetStateKey(EEnemy_States _State);
	void SetTargetKey(AActor* _pTarget);
	void SetDestination(const FVector& _Location);
	void SetDistanceToTarget(float _Distance);

private :
	UPROPERTY(EditAnywhere, Category = "Configuration")
	UBehaviorTree* m_pBehaviorTree;

	UPROPERTY()
	AEnemy_Base* m_pOwner;

	FName m_TargetKeyName;
	FName m_StateKeyName;
	FName m_DestinationKeyName;
	FName m_DistanceToTargetKeyName;
};
