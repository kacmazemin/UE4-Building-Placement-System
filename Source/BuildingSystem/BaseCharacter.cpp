// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/InputComponent.h"
#include "BuilderComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuilderComponent = CreateDefaultSubobject<UBuilderComponent>(TEXT("BuilderComponent"));
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);

	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("ToggleBuildMode",IE_Pressed, BuilderComponent, &UBuilderComponent::ToggleBuildMode);
	PlayerInputComponent->BindAction("PerformBuild",IE_Pressed, BuilderComponent, &UBuilderComponent::PerformBuild);

}

void ABaseCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ABaseCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

