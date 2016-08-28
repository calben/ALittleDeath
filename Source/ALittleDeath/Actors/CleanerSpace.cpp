// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Environment/LDTile.h"
#include "CleanerSpace.h"


// Sets default values
ACleanerSpace::ACleanerSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/Game/Materials/BaseCleanerSpaceMaterial"));
	if (MeshObj.Object && MaterialObj.Object)
	{
		Mesh->SetStaticMesh(MeshObj.Object);
		Mesh->SetMaterial(0, MaterialObj.Object);
	}
	Mesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 0.1f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetSimulatePhysics(false);
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ACleanerSpace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACleanerSpace::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (tmp_cleaning_timer >= CleaningTime)
	{
		for (ALDTile* Tile : ContactedTiles)
		{
			Tile->SetTileDamaging(false);
		}
		this->Destroy();
	}
	tmp_cleaning_timer += DeltaTime;
}

