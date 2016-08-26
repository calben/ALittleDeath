// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Actors/CleanerSpace.h"
#include "LDPlayerPawn.h"

void ALDPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALDPlayerPawn::DoPrimaryAction()
{
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
	SpawnLocation.Z = 50.f;
	ACleanerSpace* CleanerSpace = GetWorld()->SpawnActor<ACleanerSpace>(SpawnLocation, FRotator(0, 0, 0));
	this->CleanerSpace = CleanerSpace;
}

void ALDPlayerPawn::EndPrimaryAction()
{

}

