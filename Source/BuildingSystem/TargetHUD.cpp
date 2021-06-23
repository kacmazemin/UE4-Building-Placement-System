// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetHUD.h"
#include "Engine/Canvas.h"

void ATargetHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawRect(FLinearColor::Yellow, Canvas->SizeX / 2, Canvas->SizeY / 2,5, 5);

}
