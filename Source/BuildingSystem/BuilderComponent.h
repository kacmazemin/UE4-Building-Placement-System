// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuilderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGSYSTEM_API UBuilderComponent : public UActorComponent
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Config")
	float BuildDistance = 400.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Config")
	float FloorHeight = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Config")
	float GridSize = 200.f;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
private:

	bool bIsBuilderModeActive = false;

	void LineTraceForBuild() const;

	FVector GetBuildLocation() const;
	FRotator GetBuildRotation() const;

	UPROPERTY()
	class UCameraComponent* CameraComponent = nullptr;
	
};
