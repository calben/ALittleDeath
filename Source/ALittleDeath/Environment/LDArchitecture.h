// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LDArchitecture.generated.h"

UCLASS()
class ALITTLEDEATH_API ALDArchitecture : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALDArchitecture();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
};
