// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "ArenaTile.h"


// Sets default values
AArenaTile::AArenaTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/Game/Materials/ArenaTileMaterialBase"));
	if (MeshObj.Object && MaterialObj.Object)
	{
		Tile->SetStaticMesh(MeshObj.Object);
		Tile->SetMaterial(0, MaterialObj.Object);
	}
	RootComponent = Tile;
	this->SetActorScale3D(FVector::FVector(0.95f, 0.95f, 0.5f));
}

// Called when the game starts or when spawned
void AArenaTile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AArenaTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

