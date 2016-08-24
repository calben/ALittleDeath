// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Player/LDPlayerPawn.h"
#include "ALittleDeathGameMode.h"

AALittleDeathGameMode::AALittleDeathGameMode()
{
	DefaultPawnClass = ALDPlayerPawn::StaticClass();
}
