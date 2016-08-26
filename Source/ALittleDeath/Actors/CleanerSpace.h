// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CleanerSpace.generated.h"

UCLASS()
class ALITTLEDEATH_API ACleanerSpace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACleanerSpace();

	UPROPERTY(EditAnywhere)
		float CleaningTime = 3.f;

	UPROPERTY(EditAnywhere)
		float tmp_cleaning_timer;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
		TArray<class ALDTile*> ContactedTiles;
};
