// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_HideActor.generated.h"

class UMaterial;
class UCameraComponent;
class UStaticMeshComponent;
class UMaterialInterface;

//
// #. 카메라에서 직선을 쏘아(LineTrace) 직선과 충돌된 액터를 투명화 시킨다.
//
USTRUCT(BlueprintType)
struct FHideActor
{
	GENERATED_BODY()

public :
	explicit FHideActor() = default;
	explicit FHideActor(AActor* _pActor, UStaticMeshComponent* _pStaticMeshComponent, const TArray<UMaterialInterface*>& _Materials) :
		pActor(_pActor), pStaticMeshComponent(_pStaticMeshComponent), Materials(_Materials), bOverlapCheck(true){};

public :
	UPROPERTY(EditAnywhere, Category = "HideActor")
	AActor* pActor;

	UPROPERTY(EditAnywhere, Category = "HideActor")
	UStaticMeshComponent* pStaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "HideActor")
	TArray<UMaterialInterface*> Materials;

	UPROPERTY()
	bool bOverlapCheck;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_HideActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_HideActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public :
	void InitComponent(UCameraComponent* _pCamera, float _Length);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private :
	// #. 투명한 재질.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	UMaterialInterface* m_pTransparentMaterial;
	
	UPROPERTY()
	UCameraComponent* m_pCamera;

	UPROPERTY()
	float m_Length;

	UPROPERTY()
	TArray<FHideActor> m_HideActors;

	UPROPERTY()
	FTimerHandle m_hTimer;

private :
	UFUNCTION()
	void _StartTick();

	UFUNCTION()
	void _UnChideAllActor();


};
