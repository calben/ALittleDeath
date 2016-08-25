// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Player/LDBasePawn.h"
#include "Player/LDPlagueCarrierPawn.h"
#include "LDProjectile.h"


// Sets default values
ALDProjectile::ALDProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/Game/Materials/BaseProjectileMaterial"));
	if (MeshObj.Object && MaterialObj.Object)
	{
		Mesh->SetStaticMesh(MeshObj.Object);
		Mesh->SetMaterial(0, MaterialObj.Object);
	}
	Mesh->SetRelativeScale3D(FVector::FVector(0.2f, 0.2f, 0.5f));
	Mesh->SetRelativeRotation(FRotator::FRotator(90.f, 0.f, 0.f));
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ALDProjectile::TriggerEnter);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ALDProjectile::TriggerExit);

	InitialLifeSpan = 0.25f;

	RootComponent = Collision;
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALDProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALDProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALDProjectile::TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ALDBasePawn* BasePawn = Cast<ALDBasePawn>(OtherActor);
	if (BasePawn)
	{
		BasePawn->Die();
	}
}

void ALDProjectile::TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtsherBodyIndex)
{

}

