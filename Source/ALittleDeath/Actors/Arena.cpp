// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Arena.h"


// Sets default values
AArena::AArena()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/Game/Materials/ArenaFloorMaterial"));
	if (MeshObj.Object && MaterialObj.Object)
	{
		Floor->SetStaticMesh(MeshObj.Object);
		Floor->SetMaterial(0, MaterialObj.Object);
	}
	RootComponent = Floor;
}

// Called when the game starts or when spawned
void AArena::BeginPlay()
{
	Super::BeginPlay();

	SpawnArenaBoundaries();
	SpawnArenaTiles();
}

// Called every frame
void AArena::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AArena::SpawnArenaBoundaries()
{
	for (auto i = 0; i < 4; ++i)
	{
		float PosX, PosY;
		if (i < 2)
		{
			PosY = this->GetActorLocation().Y;
			PosX = (i % 2 ? this->GetActorScale().X * 50 + this->GetActorLocation().X : this->GetActorScale().X * 50 - this->GetActorLocation().X);
		}
		else {
			PosX = this->GetActorLocation().X;
			PosY = (i % 2 ? this->GetActorScale().Y * 50 + this->GetActorLocation().Y : this->GetActorScale().Y * 50 - this->GetActorLocation().Y);
		}
		AArenaWall* Wall = GetWorld()->SpawnActor<AArenaWall>(FVector::FVector(PosX, PosY, this->GetActorLocation().Z), FRotator::ZeroRotator);
		if (i < 2)
		{
			Wall->SetActorScale3D(FVector::FVector(1.0f, this->GetActorScale().Y, this->GetActorScale().Z + 0.5f));
		}
		else
		{
			Wall->SetActorScale3D(FVector::FVector(this->GetActorScale().X, 1.0f, this->GetActorScale().Z + 0.5f));
		}
		Walls.Add(Wall);
	}
}

void AArena::SpawnArenaTiles()
{
	for (auto i = 0; i < this->GetActorScale3D().X; ++i)
	{
		for (auto j = 0; j < this->GetActorScale3D().Y; ++j)
		{
			const FVector TileLocation = FVector(i * 100, j * 100, 10.f) + this->GetActorLocation() - this->GetActorRelativeScale3D() * 50;
			AArenaTile* Tile = GetWorld()->SpawnActor<AArenaTile>(TileLocation, FRotator(0, 0, 0));
			Tiles.Add(Tile);
		}
	}
}