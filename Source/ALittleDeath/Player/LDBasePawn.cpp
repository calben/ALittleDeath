// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Environment/LDTile.h"
#include "Actors/LDProjectile.h"
#include "Player/LDSharedCamera.h"
#include "Kismet/KismetMathLibrary.h"
#include "LDBasePawn.h"


// Sets default values
ALDBasePawn::ALDBasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/Game/Materials/BasePlayerMaterial"));
	if (MeshObj.Object && MaterialObj.Object)
	{
		Mesh->SetStaticMesh(MeshObj.Object);
		Mesh->SetMaterial(0, MaterialObj.Object);
	}
	Mesh->SetRelativeScale3D(FVector::FVector(0.6f, 0.6f, 1.f));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetLinearDamping(0.95f);
	Mesh->SetEnableGravity(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bDoCollisionTest = true;
	SpringArm->bAbsoluteRotation = true;
	SpringArm->RelativeRotation = FRotator(-90.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 800.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetRelativeLocation(FVector::FVector(25.f, 0.f, 0.f));

	RootComponent = Mesh;
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ALDBasePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALDBasePawn::Tick(float DeltaTime)
{
	const float MoveForwardValue = GetInputAxisValue("MoveForward");
	const float MoveRightValue = GetInputAxisValue("MoveRight");

	MoveDirection = FVector(MoveForwardValue, MoveRightValue, 0.f).GetClampedToMaxSize(1.0f);
	MoveInDirection(MoveDirection, DeltaTime);

	const float LookForwardValue = GetInputAxisValue("LookForward");
	const float LookRightValue = GetInputAxisValue("LookRight");
	LookDirection = FVector(LookForwardValue, LookRightValue, 0.f).GetClampedToMaxSize(1.0f);

	tmp_attack_action_timer += DeltaTime;
	tmp_primary_action_timer += DeltaTime;
	tmp_secondary_action_timer += DeltaTime;
}

void ALDBasePawn::MoveInDirection(FVector Direction, float DeltaTime)
{
	const FVector Movement = Direction * MoveSpeed * DeltaTime;

	if (Movement.SizeSquared() > 0.1f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
}

void ALDBasePawn::FireProjectileInDirection(FVector Direction)
{
	ALDProjectile* Projectile = GetWorld()->SpawnActor<ALDProjectile>(GetActorLocation() + 100.f * Direction, Direction.Rotation());
}

void ALDBasePawn::UpdateCurrentTile(class ALDTile* Tile)
{
	this->LastTileHovered = this->CurrentTile;
	this->CurrentTile = Tile;
}

void ALDBasePawn::Die()
{
	if (SharedCamera)
	{
		SharedCamera->WatchedPlayers.Remove(this);
	}
	this->Destroy();
}


void ALDBasePawn::DoAttackAction()
{
	if (LookDirection.SizeSquared() > 0.1f && tmp_attack_action_timer >= AttackActionDelay)
	{
		FireProjectileInDirection(LookDirection / LookDirection.Size());
		tmp_attack_action_timer = 0.f;
	}

}


void ALDBasePawn::DoPrimaryAction()
{
}


void ALDBasePawn::DoSecondaryAction()
{

}


// Called to bind functionality to input
void ALDBasePawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward");
	InputComponent->BindAxis("MoveRight");
	InputComponent->BindAxis("LookForward");
	InputComponent->BindAxis("LookRight");
	InputComponent->BindAction("PrimaryAction", IE_Pressed, this, &ALDBasePawn::DoPrimaryAction);
	InputComponent->BindAction("SecondaryAction", IE_Pressed, this, &ALDBasePawn::DoSecondaryAction);
	InputComponent->BindAction("AttackAction", IE_Pressed, this, &ALDBasePawn::DoAttackAction);
}

