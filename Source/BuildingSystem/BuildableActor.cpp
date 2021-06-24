// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/EngineTypes.h"

// Sets default values
ABuildableActor::ABuildableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(MeshComponent);
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

}

// Called when the game starts or when spawned
void ABuildableActor::BeginPlay()
{
	Super::BeginPlay();

	MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(GhostMaterial, this);

}

void ABuildableActor::OnConstruction(const FTransform& Transform)
{
	if(const UStaticMesh* SMComponent = MeshComponent->GetStaticMesh())
	{
		const FVector MeshLocation = MeshComponent->GetRelativeLocation();
	
		MeshComponent->SetRelativeLocation(FVector{
            MeshLocation.X,
            MeshLocation.Y,
            SMComponent->GetBounds().BoxExtent.Z});
 
		BoxComponent->SetBoxExtent(MeshComponent->GetStaticMesh()->GetBounds().BoxExtent);
	
	}
		
}

// Called every frame
void ABuildableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildableActor::EnableGhostMode()
{
	if(MeshComponent && GhostMaterial != nullptr)
	{
		MeshComponent->SetMaterial(0, MaterialInstanceDynamic);
		MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		BoxComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	}
}

void ABuildableActor::SetBuildableStyle()
{
	if(MaterialInstanceDynamic)
	{
		MaterialInstanceDynamic->SetVectorParameterValue(FName("BaseColorVec"), {0.25, 0.2, 0.85, 0});
	}
}

void ABuildableActor::SetCannotBuildStyle()
{
	if(MaterialInstanceDynamic)
	{
		MaterialInstanceDynamic->SetVectorParameterValue(FName("BaseColorVec"), {0.85, 0.25, 0.25, 0});
	}
}
