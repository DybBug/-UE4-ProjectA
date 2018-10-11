// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Hotkey.generated.h"

/**
 * 
 */
class UUniformGridPanel;
class UWidget_HotkeySlot;

UCLASS()
class PROJECTA_API UWidget_Hotkey : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativePreConstruct() override;
	
protected :
	UPROPERTY()
	UUniformGridPanel* m_pHotkeySlotList;
	
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWidget_HotkeySlot> m_HotkeySlotClass;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	int m_ColumnCount = 0;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TArray<FKey> m_HotkeyList;

public :
	void PressKey(int _Index);

	/* Get */
	FORCEINLINE const TArray<FKey>& GetHotkeyList() const { return m_HotkeyList; }

	FORCEINLINE const FKey& GetHotKey(int _Index) const { return m_HotkeyList[_Index]; }
	
};
