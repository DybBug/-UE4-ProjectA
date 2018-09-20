// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interface_Interaction.h"
#include "Enemy_Base.generated.h"

class UArrowComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UWidgetComponent;
class UWidget_EnemyGaugeBar;

USTRUCT(BlueprintType)
struct FEnemy_Info
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, Category = "Enemy_Info")
	FName Name;

	UPROPERTY(EditAnywhere, Category = "Enemy_Info")
	int Level;

	UPROPERTY(EditAnywhere, Category = "Enemy_Info")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Enemy_Info")
	float CurrHealth;

	UPROPERTY(EditAnywhere, Category = "Enemy_Info")
	float ExperienceToAcquire;

	UPROPERTY(EditAnywhere, Category = "Enemy_Info")
	float AttackPower;

	UPROPERTY(EditAnywhere, Category = "Enemy_Info")
	float DefensivePower;

	UPROPERTY(EditAnywhere, Category = "Enemy_Info")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Enemy_Info")
	float RunSpeed;
};


UCLASS()
class PROJECTA_API AEnemy_Base : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public :
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

	void Die(float _DeleteTime = 0.f);

	/* Interface */
	virtual void OnInteract(APlayer_Character* _pPlayer) override;
	virtual void UnInteract() override;

protected :
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* m_pArrow;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* m_pCollision;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* m_pMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UWidgetComponent* m_pWidget;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FEnemy_Info m_Info;

	UWidget_EnemyGaugeBar* m_pEnemyGaugeBarWidget;
	

public :
	FORCEINLINE const FEnemy_Info& GetInfo() const { return m_Info; }
	
};
