// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/CollisionProfile.h"

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
	BoxComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

}

// Called when the game starts or when spawned
void ABuildableActor::BeginPlay()
{
	Super::BeginPlay();


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
		MeshComponent->SetMaterial(0, GhostMaterial);
		MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		BoxComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

