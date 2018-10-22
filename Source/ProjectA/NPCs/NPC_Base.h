// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC_Base.generated.h"

class USkeletalMeshComponent;
class UArrowComponent;
class UCapsuleComponent;
class UComponent_Quest;

struct FQuest_Info;


UCLASS()
class PROJECTA_API ANPC_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private :
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* m_pArrow;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* m_pCollision;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* m_pMesh;

	UPROPERTY(EditAnywhere, Category = "Configuration|Quest")
	TArray<FQuest_Info> m_QuestInfo;

	
	
};
