// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Base.h"
#include "ProjectA.h"
#include "Enemy_Controller.h"
#include "Players/Player_Character.h"
#include "Widgets/Misc/Widget_EnemyGaugeBar.h"
#include "Actors/Chest.h"
#include "Actors/SpawnActor.h"
#include "Skills/Skill_Base.h"
#include "Items/Item_Base.h"

#include <Components/ArrowComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/WidgetComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Animation/AnimInstance.h>
#include <Engine.h>

// Sets default values
AEnemy_Base::AEnemy_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionObjectType(UEngineTypes::ConvertToCollisionChannel(OTQ_Enemy));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(UEngineTypes::ConvertToCollisionChannel(OTQ_Equipment), ECollisionResponse::ECR_Overlap);

	m_pWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	m_pWidget->SetWidgetSpace(EWidgetSpace::Screen);
	m_pWidget->SetDrawAtDesiredSize(true);
	m_pWidget->SetupAttachment(RootComponent);

	m_pChestSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ChestSpawnPoint"));
	m_pChestSpawnPoint->SetupAttachment(RootComponent);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();

	for (auto& SkillClass : m_Info.SkillClassList)
	{
		ASkill_Base* pSkill = GetWorld()->SpawnActor<ASkill_Base>(SkillClass);
		m_Skills.Add(pSkill);
	}
}

void AEnemy_Base::InitEnemy(const FVector& _Location, ASpawnActor* _pSpawnActor, int _ID)
{
	SetActorLocation(_Location);
	m_pSpawnActor = _pSpawnActor;
	m_ID = _ID;
	m_State = EEnemy_States::Search;

	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	AEnemy_Base* pCDO = GetClass()->GetDefaultObject<AEnemy_Base>();
	m_Info = pCDO->GetInfo();

	if (m_pWidget->GetUserWidgetObject())
	{
		m_pEnemyGaugeBarWidget = Cast<UWidget_EnemyGaugeBar>(m_pWidget->GetUserWidgetObject());
		m_pEnemyGaugeBarWidget->InitWidget(this);
		m_pEnemyGaugeBarWidget->UpdateWidget();
		m_pEnemyGaugeBarWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetController())
	{
		m_pAIController = Cast<AEnemy_Controller>(GetController());
		m_pAIController->Possess(this);
		m_pAIController->SetStateKey(m_State);
	}

	GetCharacterMovement()->MaxWalkSpeed = m_Info.WalkSpeed;
}

void AEnemy_Base::UpdateWidget()
{
	m_pEnemyGaugeBarWidget->UpdateWidget();
}

void AEnemy_Base::Respawn()
{
	if (m_pSpawnActor)
	{
		m_pSpawnActor->Spawn(this);
	}
}

float AEnemy_Base::TakeDamage(
	float DamageAmount,
	struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator,
	AActor* DamageCauser)
{
	if (m_Info.Health > 0.f)
	{
		m_pAIController->SetTargetKey(DamageCauser);

		m_Info.Health -= DamageAmount;
	}

	if (m_Info.Health <= 0.f)
	{
		ModifyState(EEnemy_States::Dead);
	}

	m_pEnemyGaugeBarWidget->UpdateWidget();
	
	return 0.f;
}

float AEnemy_Base::GetMaxHealth()
{
	return GetClass()->GetDefaultObject<AEnemy_Base>()->GetInfo().Health;
}

void AEnemy_Base::Walking()
{
	GetCharacterMovement()->MaxWalkSpeed = m_Info.WalkSpeed;
}

void AEnemy_Base::Running()
{
	GetCharacterMovement()->MaxWalkSpeed = m_Info.RunSpeed;
}

void AEnemy_Base::DropChest()
{
	if (m_Info.DropItemClassList.Num())
	{
		TMap<TSubclassOf<AItem_Base>, int> ItemClasses;
		for (auto& DropItem : m_Info.DropItemClassList)
		{
			int Amount = (int)FMath::FRandRange(0, DropItem.Value);
			if (Amount > 0)
			{
				ItemClasses.Add(DropItem.Key, Amount);
			}
		}

		if (ItemClasses.Num())
		{
			AChest* pChest = GetWorld()->SpawnActor<AChest>(m_pChestSpawnPoint->GetComponentLocation(), m_pChestSpawnPoint->GetComponentRotation());
			pChest->AddItemClasses(ItemClasses);
		}
	}
}

void AEnemy_Base::ModifyState(EEnemy_States _State)
{
	m_State = _State;
	m_pAIController->SetStateKey(_State);
}

float AEnemy_Base::UseSkillBy(TSubclassOf<ASkill_Base> _SkillClass)
{
	for (auto Skill : m_Skills)
	{
		if (Skill->GetClass() == _SkillClass)
		{
			Skill->InitSkill(nullptr, this);
			Skill->Use();
			return Skill->AnimLength();
		}
	}
	return 0.f;
}

void AEnemy_Base::OnInteract(APlayer_Character* _pUser)
{
	if (!GetInteractionUser())
	{
		if (_pUser->GetTarget() && _pUser->GetTarget() != this)
		{
			Cast<IInterface_Interaction>(_pUser->GetTarget())->UnInteract();
		}

		GetMesh()->SetRenderCustomDepth(true);
		SetInteractionUser(_pUser);
		GetInteractionUser()->LockOn(this);
		
		m_pEnemyGaugeBarWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_pEnemyGaugeBarWidget->UpdateWidget();
	}
}

void AEnemy_Base::UnInteract()
{
	if (GetInteractionUser())
	{
		GetMesh()->SetRenderCustomDepth(false);
		GetInteractionUser()->LockOff();
		SetInteractionUser(nullptr);
		m_pEnemyGaugeBarWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

