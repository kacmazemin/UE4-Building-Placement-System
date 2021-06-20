// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "BuildableActor.h"

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

void UBuilderComponent::LineTraceForBuild()
{
	FHitResult HitResult;
	FVector StartLocation;
	FVector EndLocation;
	FCollisionQueryParams QueryParams;


	if(CameraComponent)
	{
		StartLocation = CameraComponent->GetComponentLocation();
		EndLocation = StartLocation + CameraComponent->GetForwardVector() * 500.f;
	}

	if(CurrentBuildableActor != nullptr)
	{
		QueryParams.AddIgnoredActor(CurrentBuildableActor);
	}
		
	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, QueryParams))
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Magenta, false, 1.f);
		if(CurrentBuildableActor == nullptr)
		{
			CurrentBuildableActor = GetWorld()->SpawnActor<ABuildableActor>(BuildableActor, GetBuildLocation(), CurrentRotation, FActorSpawnParameters());
			CurrentBuildableActor->EnableGhostMode();
		}
		else
		{
			CurrentBuildableActor->SetActorLocationAndRotation(GetBuildLocation(), CurrentRotation);
		}

		if(const auto BuildableActorRef = Cast<ABuildableActor>((HitResult.GetActor())))
		{
			const FVector InverseVector = BuildableActorRef->GetActorTransform().InverseTransformPosition(HitResult.Location);
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, InverseVector.ToString());
		}
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
	const FRotator Rotation = CameraComponent->GetComponentRotation();

	return FRotator(0, FMath::GridSnap(Rotation.Yaw, 90.f), 0);
}

void UBuilderComponent::ToggleBuildMode()
{
	bIsBuilderModeActive = !bIsBuilderModeActive;
}

void UBuilderComponent::PerformBuild()
{
	if(bIsBuilderModeActive && CurrentBuildableActor != nullptr)
	{
		const ABuildableActor* SpawnedActor = GetWorld()->SpawnActor<ABuildableActor>(BuildableActor, GetBuildLocation(), CurrentRotation, FActorSpawnParameters());

	}
}

void UBuilderComponent::RotateBuild()
{
	if(bIsBuilderModeActive && CurrentBuildableActor != nullptr)
	{
		if(CurrentRotation.Yaw == 90 || CurrentRotation.Yaw == 270)
		{
			CurrentRotation.Yaw = 0;
		}
		else if(CurrentRotation.Yaw == 0 || CurrentRotation.Yaw == 180 || CurrentRotation.Yaw == 360 )
		{
			CurrentRotation.Yaw = 90;
		}
	}
}