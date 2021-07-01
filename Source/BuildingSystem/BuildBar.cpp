// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildBar.h"

#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "BuildableActor.h"
#include "MyButton.h"

void UBuildBar::Init(const TArray<TSubclassOf<ABuildableActor>>& BuildList)
{
	MyList = BuildList;
	
	if(BarHorizontalBox != nullptr)
	{
		for (const auto Element : BuildList)
		{
			UMyButton* Button = WidgetTree->ConstructWidget<UMyButton>(UMyButton::StaticClass());
			Button->Initialize(Element);
			
			BarHorizontalBox->AddChild(Button);

			if(UHorizontalBoxSlot* HBoxSlot = Cast<UHorizontalBoxSlot>(Button->Slot))
			{
				HBoxSlot->SetSize(ESlateSizeRule::Fill);
			}
		}
	}
}
