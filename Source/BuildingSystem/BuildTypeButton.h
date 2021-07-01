// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BuilderComponent.h"
#include "Components/Button.h"
#include "BuildTypeButton.generated.h"

class ABuildableActor;

/**
 * 
 */
UCLASS()
class BUILDINGSYSTEM_API UMyButton : public UButton
{
	GENERATED_BODY()
public:
	
	void Initialize(const TSubclassOf<ABuildableActor> Build);

private:

	UFUNCTION()
	void OnClickFunc();

	TSubclassOf<ABuildableActor> SubClass = nullptr;
};
