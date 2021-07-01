// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildTypeButton.h"
#include "BaseCharacter.h"

void UMyButton::Initialize(const TSubclassOf<ABuildableActor> Build)
{
	SubClass = Build;
	OnClicked.AddDynamic(this, &UMyButton::OnClickFunc);
}

void UMyButton::OnClickFunc()
{
	if(auto Player = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		Player->BuilderComponent->OnChangeBuildDelegate.Broadcast(SubClass);
	}
}
