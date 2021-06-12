// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderComponent.h"

// Sets default values for this component's properties
UBuilderComponent::UBuilderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UBuilderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Called when the game starts
void UBuilderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UBuilderComponent::ToggleBuildMode()
{
	bIsBuilderModeActive = !bIsBuilderModeActive ? true : false;
}

void UBuilderComponent::PerformBuild()
{
	if(bIsBuilderModeActive)
	{
		//todo
	}
}

