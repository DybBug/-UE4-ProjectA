// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Component_Base.h"
#include "ProjectA_Enums.h"
#include "Component_Stat.generated.h"

class UWidget_StatBar;
class UWidget_StatEntry;

USTRUCT(BlueprintType)
struct FStat_Info
{
	GENERATED_BODY();

	FStat_Info() :
		MaxValue(0.f), CurrentValue(0.f) {};

	FStat_Info(EStat_Types _Type, float _Max, float _Current) :
		MaxValue(_Max), CurrentValue(_Current) {};

public :
	// #. 스탯의 최대 값.
	UPROPERTY(EditAnywhere, Category = "Stat_Info")
	float MaxValue;

	// #. 스탯의 현재 값.
	UPROPERTY(EditAnywhere, Category = "Stat_Info")
	float CurrentValue;

	// #. 레벨업 당 스탯 증가치.
	UPROPERTY(EditAnywhere, Category = "Stat_Info")
	float IncreasePerLevelUp;

	// #. 포인트 당 스탯 증가치.
	UPROPERTY(EditAnywhere, Category = "Stat_Info")
	float IncreasePerPoint;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UComponent_Stat : public UComponent_Base
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Stat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected :
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TMap<EStat_Types, FStat_Info> m_Stats;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	int m_StatPoint;

	int m_UsedStatPoint;

	TArray<UWidget_StatEntry*> m_pEntryWidgets;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TMap<EStat_Types, UWidget_StatBar*> m_StatBarWidgets;

public :
	virtual void InitComponent(UWidget_Base* _pWidget) override;

	bool AddWidget(EStat_Types _Type, UWidget_StatBar* const _pWidget);
	void AddStatPoint(float _Value);

	void ModifyStatPoint(float _Value);
	void ModifyMaxValueByType(const EStat_Types& _Type, float _Value = 0.f);
	void ModifyCurrentValueByType(const EStat_Types& _Type, float _Value = 0.f);
	void ModifyIncreasePerLevelUpByType(const EStat_Types& _Type, float _Value = 0.f);
	void ModifyIncreasePerPointByType(const EStat_Types& _Type, float _Value = 0.f);

	void Apply();
	void Cancel();

	void SetEntryWidget(UWidget_StatEntry* const& _pWidget);

	/* Get */
	FORCEINLINE const int& GetStatPoint() const { return m_StatPoint; }
	FORCEINLINE const int& GetUsedStatPoint() const { return m_UsedStatPoint; }

	FORCEINLINE const TMap<EStat_Types, FStat_Info>& GetStats() const { return m_Stats; }
	FORCEINLINE const FStat_Info& GetStat(EStat_Types _Type) const { return m_Stats[_Type]; }

	/* Set */
	FORCEINLINE void SetStat(EStat_Types _Type, const FStat_Info& _Stat) { m_Stats[_Type] = _Stat; }
};

