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
	if (LookDirection.SizeSquared() > 0.1f && tmp_primary_action_timer >= PrimaryActionDelay)
	{
		FVector SpawnLocation = GetActorLocation() + LookDirection * 175.f;
		SpawnLocation.Z = 50.f;
		ACleanerSpace* CleanerSpace = GetWorld()->SpawnActor<ACleanerSpace>(SpawnLocation, FRotator(0, 0, 0));
		this->CleanerSpace = CleanerSpace;
		tmp_primary_action_timer = 0.f;
	}
}

