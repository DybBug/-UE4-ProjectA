// Fill out your copyright notice in the Description page of Project Settings.

#include "Component_HideActor.h"

#include <Engine/World.h>
#include <Engine.h>
#include <Camera/CameraComponent.h>
#include <TimerManager.h>
#include <Components/StaticMeshComponent.h>

// Sets default values for this component's properties
UComponent_HideActor::UComponent_HideActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UComponent_HideActor::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UComponent_HideActor::InitComponent(UCameraComponent* _pCamera, float _Length)
{
	m_pCamera = _pCamera;
	m_Length = _Length;

	GetWorld()->GetTimerManager().SetTimer(m_hTimer, this, &UComponent_HideActor::_StartTick, 0.2f, true);
}

void UComponent_HideActor::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UComponent_HideActor::_StartTick()
{
	FVector Start = m_pCamera->GetComponentLocation();
	FVector End = Start + (m_pCamera->GetForwardVector() * m_Length);

	TArray<FHitResult> HitResults;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	if (GetWorld()->LineTraceMultiByObjectType(HitResults, Start, End, ObjectQueryParams))
	{
		::DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, 5.f);

		for (auto& HitResult : HitResults)
		{			
			// #. 기존의 투명한 벽이 다시 오버랩 됬는지 확인.
			for (auto& HideActor : m_HideActors)
			{
				if (!HideActor.bOverlapCheck && (HideActor.pActor == HitResult.GetActor()))
				{
					HideActor.bOverlapCheck = true;
					break;
				}
			}

			// #. 새로 오버랩된 액터 저장하기.
			if (HitResult.GetComponent()->GetMaterial(0) != m_pTransparentMaterial)
			{
				if (UStaticMeshComponent* pStaticMeshComponent = Cast<UStaticMeshComponent>(HitResult.GetComponent()))
				{
					m_HideActors.Add(FHideActor(HitResult.GetActor(), pStaticMeshComponent, pStaticMeshComponent->GetMaterials()));
					for (int i = 0; i < m_HideActors.Last().Materials.Num(); ++i)
					{
						m_HideActors.Last().pStaticMeshComponent->SetMaterial(i, m_pTransparentMaterial);
					}
				}
			}			
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, UKismetSystemLibrary::GetDisplayName(HitResult.GetActor()));
		}

		// #. 더이상 오버랩되지 않은 액터들을 다시 불투명하게 변경.
		TArray<FHideActor> TempActors;
		bool bRemove = false;
		for (auto& HideActor : m_HideActors)
		{
			if (HideActor.bOverlapCheck == false)
			{
				for (int i = 0; i < HideActor.Materials.Num(); ++i)
				{
					HideActor.pStaticMeshComponent->SetMaterial(i, HideActor.Materials[i]);
					bRemove = true;
				}
			}	
			else
			{
				TempActors.Add(HideActor);
			}
			HideActor.bOverlapCheck = false;
		}

		// #. 기존의 투명한 액터들중에 삭제가 된 경우가 있으면 HideActors를 비우고 다시 재 설정.
		if (bRemove)
		{
			m_HideActors.Empty();
			m_HideActors = TempActors;
		}

		return;
	}

	_UnChideAllActor();
}

void UComponent_HideActor::_UnChideAllActor()
{
	if (m_HideActors.Num() > 0)
	{
		for (auto& HideActor : m_HideActors)
		{
			for (int i = 0; i < HideActor.Materials.Num(); ++i)
			{
				HideActor.pStaticMeshComponent->SetMaterial(i, HideActor.Materials[i]);
			}
		}
		m_HideActors.Empty();
	}
}

