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
		EndLocation = StartLocation + CameraComponent->GetForwardVector() * 20000.f;
	}

	if(CurrentBuildableActor != nullptr)
	{
		QueryParams.AddIgnoredActor(CurrentBuildableActor);
	}
		
	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, QueryParams))
	{
		if(CurrentBuildableActor == nullptr)
		{
			CurrentBuildableActor = GetWorld()->SpawnActor<ABuildableActor>(BuildableActor, HitResult.Location, CurrentRotation, FActorSpawnParameters());
			CurrentBuildableActor->EnableGhostMode();
		}
		else
		{
			TArray<AActor*> OverlappingActors;
			CurrentBuildableActor->GetOverlappingActors(OverlappingActors, ABuildableActor::StaticClass());

			if(OverlappingActors.Num() > 0)
			{
				CurrentBuildableActor->SetCannotBuildStyle();
				bCanBuild = false;
			}
			else
			{
				CurrentBuildableActor->SetBuildableStyle();
				bCanBuild = true;
			}
			
			CurrentBuildableActor->SetActorLocationAndRotation(HitResult.Location, CurrentRotation);

		}

		if(const auto BuildableActorRef = Cast<ABuildableActor>((HitResult.GetActor())))
		{
			const FVector InverseVector = BuildableActorRef->GetActorTransform().InverseTransformPosition(HitResult.Location);

			//todo add dynmic offset logic 
			float OffSetX = 0; 
			float OffSetY = 0; 
			
			if(FMath::Abs(InverseVector.X) > FMath::Abs(InverseVector.Y))
			{
				OffSetX = 401 * FMath::Sign(InverseVector.X);
			}
			else
			{
				OffSetY = 401 * FMath::Sign(InverseVector.Y);
			}
			
			CurrentBuildableActor->SetActorLocationAndRotation(BuildableActorRef->GetActorTransform().GetLocation(), CurrentRotation);
			CurrentBuildableActor->AddActorLocalOffset(FVector{OffSetX, OffSetY, 0});
		}
	}
}

void UBuilderComponent::ToggleBuildMode()
{
	bIsBuilderModeActive = !bIsBuilderModeActive;
}

void UBuilderComponent::PerformBuild()
{
	if(bCanBuild && bIsBuilderModeActive && CurrentBuildableActor != nullptr)
	{
		 GetWorld()->SpawnActor<ABuildableActor>(BuildableActor, CurrentBuildableActor->GetActorLocation(), CurrentRotation, FActorSpawnParameters());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Build Position is wrong"));
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