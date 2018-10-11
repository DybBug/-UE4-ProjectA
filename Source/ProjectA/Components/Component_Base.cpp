// Fill out your copyright notice in the Description page of Project Settings.

#include "Component_Base.h"
#include "Widgets/Widget_Base.h"


// Sets default values for this component's properties
UComponent_Base::UComponent_Base()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	m_pWidget = nullptr;
	m_bIsOpen = false;
}


// Called when the game starts
void UComponent_Base::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UComponent_Base::InitComponent(UWidget_Base* _pWidget)
{
	m_pWidget = _pWidget;
}

void UComponent_Base::UpdateComponent()
{

}

void UComponent_Base::Open()
{
	if (!m_bIsOpen)
	{
		m_bIsOpen = true;
		m_pWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UComponent_Base::Close()
{
	if (m_bIsOpen)
	{
		m_bIsOpen = false;
		m_pWidget->SetVisibility(ESlateVisibility::Hidden);

	}
}


