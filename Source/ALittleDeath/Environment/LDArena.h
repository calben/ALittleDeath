// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LDArena.generated.h"

UCLASS()
class ALITTLEDEATH_API ALDArena : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALDArena();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		TArray<class ALDTile*> Tiles;

	UPROPERTY(EditAnywhere)
		UMaterial* TileMaterialA;

	UPROPERTY(EditAnywhere)
		UMaterial* TileMaterialB;

	void SpawnBoardTiles();
	
};
