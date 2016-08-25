// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/LDBasePawn.h"
#include "LDPlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class ALITTLEDEATH_API ALDPlayerPawn : public ALDBasePawn
{
	GENERATED_BODY()

		virtual void DoPrimaryAction() override;
	
	virtual void Tick(float DeltaTime) override;
};
