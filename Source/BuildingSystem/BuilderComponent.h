// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuilderComponent.generated.h"

class ABuildableActor;
class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeBuildDelegate, TSubclassOf<ABuildableActor>, BuildActor);

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
	
	UFUNCTION(BlueprintCallable)
	void ChangeBuild(TSubclassOf<ABuildableActor> BuildActor);

	TSubclassOf<ABuildableActor> BuildableActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TArray<TSubclassOf<ABuildableActor>> BuildableActors;

	UPROPERTY(BlueprintAssignable)
	FOnChangeBuildDelegate OnChangeBuildDelegate;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	float SpaceBetweenMeshes = 0.5f;
	
	bool bCanBuild = false;

	bool bIsBuilderModeActive = false;

	void LineTraceForBuild();

	UPROPERTY()
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY()
	ABuildableActor* CurrentBuildableActor = nullptr;

	FRotator CurrentRotation = FRotator::ZeroRotator;
};
