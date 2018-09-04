// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Detail.h"
#include "../Widget_Main.h"
#include "Items/Item_Base.h"

#include <WidgetTree.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>

#define LOCTEXT_NAMESPACE "Format"

void UWidget_Detail::InitWidget(UWidget_Main* _pWidget)
{
	m_pMainWidget = _pWidget;
	for (int i = 0; i < (int)EStat_Types::Max; ++i)
	{
		UTextBlock* pTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		pTextBlock->SetVisibility(ESlateVisibility::Collapsed);
		m_pAbilityList->AddChildToVerticalBox(pTextBlock);
	}
}

void UWidget_Detail::UpdateWidget(TSubclassOf<AItem_Base> _ItemClass)
{
	const FItem_Info& ItemInfo = _ItemClass.GetDefaultObject()->GetInfo();

	// #. 아이콘.
	m_pIcon->SetBrushFromTexture(ItemInfo.pIcon);
	
	// #. 이름.
	m_pNameText->SetText(FText::FromName(ItemInfo.Name));

	// #. 설명.
	FString Description = ItemInfo.Description.ToString().Replace(L"/n", L"\n");
	m_pDescriptionText->SetText(FText::FromString(Description));

	// #. 능력치.
	if (!ItemInfo.AbilityList.Num())
	{
		m_pAbilityContain->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		m_pAbilityContain->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		for (int i = 0; i < (int)EStat_Types::Max; ++i)
		{			
			if (ItemInfo.AbilityList.Contains(EStat_Types(i)))
			{
				UTextBlock* pTextBlock = Cast<UTextBlock>(m_pAbilityList->GetChildAt(i));

				FString StatTypeStr = CONVERT_DISPLAYNAME_TO_STRING(L"EStat_Types", EStat_Types(i));
				FText Format = FText::Format(LOCTEXT("Format", "{0} : {1}"), FText::FromString(StatTypeStr), ItemInfo.AbilityList[EStat_Types(i)]);
				pTextBlock->SetText(Format);
				pTextBlock->Font.Size = 18;
				pTextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
			{
				UTextBlock* pTextBlock = Cast<UTextBlock>(m_pAbilityList->GetChildAt(i));
				pTextBlock->SetVisibility(ESlateVisibility::Collapsed);
			}

		}
	}
}

#undef LOCTEXT_NAMESPACE
