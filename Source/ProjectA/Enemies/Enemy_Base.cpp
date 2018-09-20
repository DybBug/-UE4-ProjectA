// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Base.h"
#include "ProjectA.h"
#include "Players/Player_Character.h"
#include "Widgets/Misc/Widget_EnemyGaugeBar.h"

#include <Components/ArrowComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/WidgetComponent.h>


// Sets default values
AEnemy_Base::AEnemy_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = m_pArrow;

	m_pCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	m_pCollision->SetCollisionObjectType(UEngineTypes::ConvertToCollisionChannel(OTQ_Enemy));
	m_pCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_pCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	m_pCollision->SetCollisionResponseToChannel(UEngineTypes::ConvertToCollisionChannel(OTQ_Equipment), ECollisionResponse::ECR_Overlap);
	m_pCollision->SetupAttachment(RootComponent);

	m_pMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetupAttachment(RootComponent);

	m_pWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	m_pWidget->SetWidgetSpace(EWidgetSpace::Screen);
	m_pWidget->SetDrawAtDesiredSize(true);
	m_pWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();

	if (m_pWidget->GetUserWidgetObject())
	{
		m_pEnemyGaugeBarWidget = Cast<UWidget_EnemyGaugeBar>(m_pWidget->GetUserWidgetObject());
		m_pEnemyGaugeBarWidget->InitWidget(this);
		m_pEnemyGaugeBarWidget->UpdateWidget();
		m_pEnemyGaugeBarWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

float AEnemy_Base::TakeDamage(
	float DamageAmount,
	struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator,
	AActor* DamageCauser)
{

	m_Info.CurrHealth -=(DamageAmount - m_Info.DefensivePower);
	m_pEnemyGaugeBarWidget->UpdateWidget();

	if (m_Info.CurrHealth <= 0.f)
	{
		Die(2.f);
	}
	return 0.f;
}

void AEnemy_Base::Die(float _DeleteTime /*= 0.f*/)
{
	UnInteract();
	m_pCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	m_pEnemyGaugeBarWidget->SetVisibility(ESlateVisibility::Hidden);
	SetLifeSpan(_DeleteTime);
}

void AEnemy_Base::OnInteract(APlayer_Character* _pPlayer)
{
	if (!m_pPlayer)
	{
		if (_pPlayer->GetTarget() && _pPlayer->GetTarget() != this)
		{
			Cast<IInterface_Interaction>(_pPlayer->GetTarget())->UnInteract();
		}

		m_pMesh->SetRenderCustomDepth(true);
		m_pPlayer = _pPlayer;
		m_pPlayer->LockOn(this);
		m_pEnemyGaugeBarWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_pEnemyGaugeBarWidget->UpdateWidget();
	}
}

void AEnemy_Base::UnInteract()
{
	if (m_pPlayer)
	{
		m_pMesh->SetRenderCustomDepth(false);
		m_pPlayer->LockOff();
		m_pPlayer = nullptr;
		m_pEnemyGaugeBarWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}


