// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TargetHUD.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGSYSTEM_API ATargetHUD : public AHUD
{
	GENERATED_BODY()

private:
	virtual void DrawHUD() override;

	
};
