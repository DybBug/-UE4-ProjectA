// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectA_Enums.h"
#include "Interfaces/Interface_Interaction.h"
#include "Enemy_Base.generated.h"

class UWidgetComponent;
class AEnemy_Controller;
class UWidget_EnemyGaugeBar;
class AItem_Base;
class ASpawnActor;
class ASkill_Base;

USTRUCT(BlueprintType)
struct FEnemy_Info
{
	GENERATED_BODY()

public :
	// #. 이름.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	FName Name;

	// #. 레벨.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	int Level;

	// #. 체력.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	float Health;

	// #. 적 처치시 습득할 경험치.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	float ExperienceToAcquire;

	// #. 공격력.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	float AttackPower;

	// #. 방어력.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	float DefensivePower;

	// #. 걷기 속도.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	float WalkSpeed;

	// #. 달리기 속도.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	float RunSpeed;

	// #. 시야각
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	float AngleOfView;

	// #. 드랍 아이템 리스트.(아이템, 최대 수량)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	TMap<TSubclassOf<AItem_Base>, uint8> DropItemClassList;

	// #. 스킬 리스트.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy_Info")
	TArray<TSubclassOf<ASkill_Base>> SkillClassList;
};


UCLASS()
class PROJECTA_API AEnemy_Base : public ACharacter, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private :	
	UPROPERTY()
	AEnemy_Controller* m_pAIController;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	int m_ID;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UWidgetComponent* m_pWidget;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* m_pChestSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FEnemy_Info m_Info;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	EEnemy_States m_State;

	// #. 탐색 범위.
	// #. 해당 범위 안에 있으면 추적함.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	float m_SearchRange;

	// #. 전투 범위.
	// #. 해당 범위안에 있으면 공격함.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	float m_BattleRange;

	UPROPERTY()
	ASpawnActor* m_pSpawnActor;

	UPROPERTY()
	UWidget_EnemyGaugeBar* m_pEnemyGaugeBarWidget;

	UPROPERTY()
	TArray<ASkill_Base*> m_Skills;

public:
	void InitEnemy(const FVector& _Location, ASpawnActor* _pSpawnActor, int _ID);
	void UpdateWidget();
	void Respawn();

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

	float GetMaxHealth();

	void Walking();
	void Running();

	void DropChest();

	UFUNCTION(BlueprintCallable)
	void ModifyState(EEnemy_States _State);

	UFUNCTION(BlueprintCallable)
	float UseSkillBy(TSubclassOf<ASkill_Base> _SkillClass);

	/* Interface */
	virtual void OnInteract(APlayer_Character* _pPlayer) override;
	virtual void UnInteract() override;

	/* Get */
	UFUNCTION(BlueprintPure)
	const FEnemy_Info& GetInfo() const { return m_Info; }

	UFUNCTION(BlueprintPure)
	EEnemy_States GetState() const { return m_State;  }

	UFUNCTION(BlueprintPure)
	int GetID() const { return m_ID; }

	UFUNCTION(BlueprintPure)
	float GetSerachRange() const { return m_SearchRange;  }

	UFUNCTION(BlueprintPure)
	float GetBattleRange() const { return m_BattleRange; }
};
