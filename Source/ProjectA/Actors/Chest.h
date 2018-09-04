// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interface_Interaction.h"
#include "Chest.generated.h"

class USphereComponent;
class UArrowComponent;
class UStaticMeshComponent;
class UComponent_Pickup;

UCLASS()
class PROJECTA_API AChest : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected :
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* m_pCollision;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* m_pArrow;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* m_pMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UComponent_Pickup* m_pPickup;

public :
	/* Interface */
	virtual void OnInteract(APlayer_Character* _pPlayer) override;
	virtual void UnInteract() override;

	
	
};
