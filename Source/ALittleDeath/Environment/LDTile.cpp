// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Environment/LDArena.h"
#include "Player/LDBasePawn.h"
#include "Player/LDPlagueCarrierPawn.h"
#include "LDTile.h"


// Sets default values
ALDTile::ALDTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	if (MeshObj.Object)
	{
		Mesh->SetStaticMesh(MeshObj.Object);
	}
	RootComponent = Mesh;
	this->SetActorScale3D(FVector::FVector(0.95f, 0.95f, 0.1f));

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector::FVector(50.f, 50.f, 2000.f));
	Collision->SetRelativeLocation(FVector::FVector(0.f, 0.f, 300.f));
	Collision->bGenerateOverlapEvents = true;
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ALDTile::TriggerEnter);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ALDTile::TriggerExit);
	Collision->SetupAttachment(Mesh);

	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObjDamaging(TEXT("/Game/Materials/TileMaterialDamaging"));
	TileMaterialDamaging = MaterialObjDamaging.Object;
}

// Called when the game starts or when spawned
void ALDTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALDTile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void ALDTile::TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ALDBasePawn* BasePawn = Cast<ALDBasePawn>(OtherActor);
	if (BasePawn)
	{
		BasePawn->UpdateCurrentTile(this);
	}

	ALDPlagueCarrierPawn* PlagueCarrierPawn = Cast<ALDPlagueCarrierPawn>(OtherActor);
	if (PlagueCarrierPawn)
	{
		this->SetTileDamaging(true);
	}
}

void ALDTile::TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ALDTile::SetTileDamaging(bool ShouldDamage, float DPS)
{
	if (ShouldDamage)
	{
		this->Mesh->SetMaterial(0, TileMaterialDamaging);
		this->bTileDamaging = true;
		this->TileDamagePerSecond = DPS;
	}
	else
	{

	}
}

TArray<ALDTile*> ALDTile::GetAdjacentTiles()
{
	return Arena->GetTilesAdjacentTo(this);
}
