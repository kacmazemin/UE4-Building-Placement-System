// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildableActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABuildableActor::ABuildableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABuildableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

