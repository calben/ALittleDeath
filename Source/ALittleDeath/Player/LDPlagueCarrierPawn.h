// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/LDBasePawn.h"
#include "LDPlagueCarrierPawn.generated.h"

/**
 * 
 */
UCLASS()
class ALITTLEDEATH_API ALDPlagueCarrierPawn : public ALDBasePawn
{
	GENERATED_BODY()

public:

		ALDPlagueCarrierPawn();

	UPROPERTY(EditAnywhere)
		bool bUseHeuristicAI;

	UPROPERTY(EditAnywhere)
		class ALDTile* TargetTile;
	
	virtual void Tick(float DeltaSeconds) override;

	void ChooseNewTarget();

	virtual void Die() override;
};
