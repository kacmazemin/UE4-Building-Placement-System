// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderComponent.h"

#include "AssetRegistryModule.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "BuildableActor.h"

// Sets default values for this component's properties
UBuilderComponent::UBuilderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

	if(BuildableActors.Num() > 0)
	{
		BuildableActor = BuildableActors[0];
	}
	
	OnChangeBuildDelegate.AddDynamic(this, &UBuilderComponent::ChangeBuild);

	if(OnChangeBuildDelegate.IsBound())
	{
		GEngine->AddOnScreenDebugMessage(-1,1.f,FColor::Blue, TEXT("Binded"));
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
		if(CurrentBuildableActor == nullptr && BuildableActor != nullptr)
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

			float OffSetX = 0.f;
			float OffSetY = 0.f;
		
			if(FMath::Abs(InverseVector.X) > FMath::Abs(InverseVector.Y))
			{
				OffSetX = (BuildableActorRef->GetMeshOffset().X * .5f +
						   CurrentBuildableActor->GetMeshOffset().X * .5f +
						   (SpaceBetweenMeshes)) * FMath::Sign(InverseVector.X);
			}
			else
			{
				OffSetY = (BuildableActorRef->GetMeshOffset().Y * .5f +
						   CurrentBuildableActor->GetMeshOffset().Y * .5f +
						   (SpaceBetweenMeshes)) * FMath::Sign(InverseVector.Y);
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

//todo add localOffsetRotation
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

void UBuilderComponent::ChangeBuild(TSubclassOf<ABuildableActor> BuildActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, TEXT("WORKWORKWORK"));
	BuildableActor = BuildActor;
	
	if(CurrentBuildableActor != nullptr)
	{
		CurrentBuildableActor->Destroy();
		CurrentBuildableActor = nullptr;
	}
	
	CurrentBuildableActor = GetWorld()->SpawnActor<ABuildableActor>(BuildableActor, FVector::ZeroVector, CurrentRotation, FActorSpawnParameters());
	CurrentBuildableActor->EnableGhostMode();
}