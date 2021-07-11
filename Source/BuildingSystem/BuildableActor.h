// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildableActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;
class UMaterialInstanceDynamic;

UENUM()
enum EBuildType
{
	Unknown   UMETA(DisplayName = "Unknown"),
	Floor     UMETA(DisplayName = "Floor"),
    Wall      UMETA(DisplayName = "Wall"),
};

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

	UFUNCTION()
	void SetBuildableStyle();

	UFUNCTION()
    void SetCannotBuildStyle();

	FVector GetMeshSize() const;

	TEnumAsByte<EBuildType> GetBuildType() const { return BuildType; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent = nullptr;

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstanceDynamic = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TEnumAsByte<EBuildType> BuildType = EBuildType::Unknown;
};
