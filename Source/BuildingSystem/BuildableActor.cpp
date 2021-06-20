// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"

// Sets default values
ABuildableActor::ABuildableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	BoxCompoent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCompoent->SetupAttachment(MeshComponent);
	BoxCompoent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

}

// Called when the game starts or when spawned
void ABuildableActor::BeginPlay()
{
	Super::BeginPlay();

	if(const auto MeshComponentRef = MeshComponent->GetStaticMesh())
	{
		const FVector MeshVector = MeshComponent->GetRelativeLocation();
		
		MeshComponent->SetRelativeLocation(
			FVector{MeshVector.X, MeshVector.Y, MeshComponentRef->GetBounds().BoxExtent.Z});
		
		BoxCompoent->SetBoxExtent(MeshComponent->GetStaticMesh()->GetBounds().BoxExtent);
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
		BoxCompoent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	}
}

