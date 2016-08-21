// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "ArenaWall.h"


// Sets default values
AArenaWall::AArenaWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/Game/Materials/ArenaWallMaterial"));
	if (MeshObj.Object && MaterialObj.Object)
	{
		Wall->SetStaticMesh(MeshObj.Object);
		Wall->SetMaterial(0, MaterialObj.Object);
	}
	RootComponent = Wall;
}

// Called when the game starts or when spawned
void AArenaWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArenaWall::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

