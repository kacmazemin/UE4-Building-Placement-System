// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildableActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class BUILDINGSYSTEM_API ABuildableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildableActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void EnableGhostMode();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	UMaterial* GhostMaterial = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCompoent = nullptr;
};
