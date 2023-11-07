// Fill out your copyright notice in the Description page of Project Settings.


#include "BungBungCharacter.h"
#include "OnlineSubsystem.h"

// Sets default values
ABungBungCharacter::ABungBungCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABungBungCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABungBungCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABungBungCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

