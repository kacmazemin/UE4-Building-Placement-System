// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

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

	if(bIsBuilderModeActive)
	{
		LineTraceForBuild();		
	}
}

// Called when the game starts
void UBuilderComponent::BeginPlay()
{
	Super::BeginPlay();

	CameraComponent = GetOwner()->FindComponentByClass<UCameraComponent>();

	if(!CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("There is not any camera component"))
	}

}

void UBuilderComponent::LineTraceForBuild() const
{
	FHitResult HitResult;
	FVector StartLocation;
	FVector EndLocation;


	if(CameraComponent)
	{
		StartLocation = CameraComponent->GetForwardVector() * 2;
	}

	DrawDebugBox(GetWorld(), GetBuildLocation(), FVector(100.f,100.f,100.f), GetBuildRotation().Quaternion(), FColor::Orange);
	

	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_WorldStatic))
	{
		DrawDebugLine(GetWorld(), StartLocation, HitResult.Location, FColor::Emerald, false, 2.f);
	}
}

FVector UBuilderComponent::GetBuildLocation() const
{
	FVector Vector = CameraComponent->GetForwardVector() * BuildDistance;
	Vector += GetOwner()->GetActorLocation();

	return FVector(FMath::GridSnap(Vector.X, GridSize), FMath::GridSnap(Vector.Y, GridSize), FloorHeight);
}

FRotator UBuilderComponent::GetBuildRotation() const
{
	FRotator Rotation = CameraComponent->GetComponentRotation();

	return FRotator(0, FMath::GridSnap(Rotation.Yaw, 90.f), 0);
}

void UBuilderComponent::ToggleBuildMode()
{
	bIsBuilderModeActive = !bIsBuilderModeActive;
}

void UBuilderComponent::PerformBuild()
{
	if(bIsBuilderModeActive)
	{
		//todo
	}
}

