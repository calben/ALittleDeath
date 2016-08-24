// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Player/LDBasePawn.h"
#include "Player/LDPlagueCarrierPawn.h"
#include "PawnSpawningArea.h"


// Sets default values
APawnSpawningArea::APawnSpawningArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
}

// Called when the game starts or when spawned
void APawnSpawningArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnSpawningArea::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (SpawnedPawns.Num() < MaximumPawnCount)
	{
		if (tmp_timer >= SpawnDelay)
		{
			ALDBasePawn* BasePawn = GetWorld()->SpawnActor<ALDBasePawn>(Pawn, GetActorLocation(), FRotator(0, 0, 0));
			BasePawn->SpawnPoint = this;
			ALDPlagueCarrierPawn* PlagueCarrierPawn = Cast<ALDPlagueCarrierPawn>(BasePawn);
			if (PlagueCarrierPawn)
			{
				PlagueCarrierPawn->bUseHeuristicAI = true;
				PlagueCarrierPawn->MoveSpeed = 100;
			}
			SpawnedPawns.Add(BasePawn);
			tmp_timer = 0.f;
		}
		else
		{
			tmp_timer += DeltaTime;
		}
	}
}

