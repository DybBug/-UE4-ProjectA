// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_Base.generated.h"

class UWidget_Base;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Base();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected :
	UWidget_Base* m_pWidget;

	bool m_bIsOpen;

public :
	virtual void InitComponent(UWidget_Base* _pWidget);
	virtual void UpdateComponent();

	virtual void Open();
	virtual void Close();

	/* Get */
	FORCEINLINE UWidget_Base* const& GetWidget() const { return m_pWidget; }
	FORCEINLINE const bool& GetIsOpen() const { return m_bIsOpen; }
};
