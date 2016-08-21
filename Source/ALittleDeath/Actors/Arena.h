// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Actors/ArenaWall.h"
#include "Actors/ArenaTile.h"
#include "Arena.generated.h"

UCLASS()
class ALITTLEDEATH_API AArena : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArena();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Floor;

	UPROPERTY(EditAnywhere)
		TArray<AArenaWall*> Walls;

	UPROPERTY(EditAnywhere)
		TArray<AArenaTile*> Tiles;
	
	void SpawnArenaBoundaries();

	void SpawnArenaTiles();

};
