// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Environment/LDTile.h"
#include "Environment/PawnSpawningArea.h"
#include "LDPlagueCarrierPawn.h"

ALDPlagueCarrierPawn::ALDPlagueCarrierPawn()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_WideCapsule"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/Game/Materials/PlagueCarrierPawnMaterial"));
	if (MeshObj.Object && MaterialObj.Object)
	{
		Mesh->SetStaticMesh(MeshObj.Object);
		Mesh->SetMaterial(0, MaterialObj.Object);
	}
}

void ALDPlagueCarrierPawn::Tick(float DeltaTime)
{
	if (bUseHeuristicAI)
	{
		if (TargetTile != nullptr)
		{
			FVector tmp_location = TargetTile->GetActorLocation();
			tmp_location.Z = this->GetActorLocation().Z;
			if (FVector::Dist(this->GetActorLocation(), tmp_location) < 5.0f)
				ChooseNewTarget();
			FVector MoveDirection = TargetTile->GetActorLocation() - GetActorLocation();
			MoveDirection.Z = 0;
			MoveInDirection(MoveDirection.GetClampedToMaxSize(1.0f), DeltaTime);
		}
		else {
			ChooseNewTarget();
		}
	}
}

void ALDPlagueCarrierPawn::ChooseNewTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("CHOOSING NEW TARGET"));
	TArray<ALDTile*> CandidateTiles;
	for (ALDTile* Tile : CurrentTile->GetAdjacentTiles())
	{
		if (!Tile->bTileDamaging)
		{
			CandidateTiles.Add(Tile);
		}
	}
	if (CandidateTiles.Num() == 0)
	{
		Die();
	}
	TargetTile = CandidateTiles[FMath::FloorToInt(FMath::FRandRange(0, CandidateTiles.Num()))];
}

void ALDPlagueCarrierPawn::Die()
{
	if (this->SpawnPoint)
	{
		SpawnPoint->SpawnedPawns.Remove(this);
	}
	Destroy();
	return;

}
