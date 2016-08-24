// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PawnSpawningArea.generated.h"

UCLASS()
class ALITTLEDEATH_API APawnSpawningArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APawnSpawningArea();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALDBasePawn> Pawn;
	
	UPROPERTY(EditAnywhere)
		int MaximumPawnCount;

	UPROPERTY(EditAnywhere)
		float SpawnDelay;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
		TArray<class ALDBasePawn*> SpawnedPawns;

	UPROPERTY(EditAnywhere)
		bool bStartAI;

	float tmp_timer;
};
