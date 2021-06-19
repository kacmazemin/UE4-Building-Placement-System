// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuilderComponent.generated.h"

class ABuildableActor;
class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGSYSTEM_API UBuilderComponent final : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuilderComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ToggleBuildMode();

	UFUNCTION(BlueprintCallable)
	void PerformBuild();

	UFUNCTION(BlueprintCallable)
	void RotateBuild();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config")
	float BuildDistance = 400.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config")
	float FloorHeight = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config")
	float GridSize = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TSubclassOf<ABuildableActor> BuildableActor = nullptr;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:

	bool bIsBuilderModeActive = false;

	void LineTraceForBuild();

	FVector GetBuildLocation() const;
	FRotator GetBuildRotation() const;

	UPROPERTY()
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY()
	ABuildableActor* CurrentBuildableActor = nullptr;

	FRotator CurrentRotation = FRotator::ZeroRotator;
};
