// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectA_Enums.h"
#include "Item_Base.generated.h"

class APlayer_Character;

struct FInventorySlot_Info;


USTRUCT(BlueprintType)
struct FItem_Info
{
	GENERATED_BODY()

public :
	// #. 이름.
	UPROPERTY(EditAnywhere, Category = "Item_Info")
	FName Name = TEXT("#Unknown");

	// #. 유형.
	UPROPERTY(EditAnywhere, Category = "Item_Info")
	EItem_Types Type = EItem_Types::None;

	// #. 아이콘.
	UPROPERTY(EditAnywhere, Category = "Item_Info")
	UTexture2D* pIcon = nullptr;

	// #. 설명.
	UPROPERTY(EditAnywhere, Category = "Item_Info")
	FText Description;

	// #. 사용 가능?
	UPROPERTY(EditAnywhere, Category = "Item_Info")
	bool bCanUsed = false;

	// #. 적재 가능?
	UPROPERTY(EditAnywhere, Category = "Item_Info")
	bool bCanStacked = false;

	// #. 아이템 능력 목록.
	UPROPERTY(EditAnywhere, Category = "Item_Info")
	TMap<EStat_Types, int> AbilityList;
};

UCLASS()
class PROJECTA_API AItem_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected :
	UPROPERTY(EditAnywhere, Category = "Configuration")
	FItem_Info m_Info;

	APlayer_Character* m_pPlayer;

public :
	virtual void InitItem(AActor* _pOwner);
	virtual bool OnUse(FInventorySlot_Info* const pSlotInfo) { return false; }

	/* Get */
	FORCEINLINE const FItem_Info& GetInfo() const { return m_Info; }
	
};
