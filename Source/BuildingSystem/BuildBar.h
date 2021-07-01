// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildBar.generated.h"

class UHorizontalBox;
class ABuildableActor;
/**
 * 
 */
UCLASS()
class BUILDINGSYSTEM_API UBuildBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Init(const TArray<TSubclassOf<ABuildableActor>>& BuildList);

	TArray<TSubclassOf<ABuildableActor>> MyList;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* BarHorizontalBox = nullptr;
};
