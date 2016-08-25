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
	ACleanerSpace* CleanerSpace = GetWorld()->Spawn<CleanerSpace>(GetActorLocation(), FRotator::ZeroRotator);
}

