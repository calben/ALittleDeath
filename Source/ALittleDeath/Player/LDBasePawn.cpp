// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Environment/LDTile.h"
#include "LDBasePawn.h"


// Sets default values
ALDBasePawn::ALDBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetIntensity(1000.f);
	Light->SetLightColor(FLinearColor::FLinearColor(160.f, 250.f, 160.f), true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObj(TEXT("/Game/Materials/BasePlayerMaterial"));
	if (MeshObj.Object && MaterialObj.Object)
	{
		Mesh->SetStaticMesh(MeshObj.Object);
		Mesh->SetMaterial(0, MaterialObj.Object);
	}
	Mesh->SetRelativeScale3D(FVector::FVector(0.6f, 0.6f, 0.4f));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetLinearDamping(0.95f);
	Mesh->SetEnableGravity(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bDoCollisionTest = true;
	SpringArm->bAbsoluteRotation = true;
	SpringArm->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 700.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;

	RootComponent = Mesh;
	Light->SetupAttachment(Mesh);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ALDBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALDBasePawn::Tick( float DeltaTime )
{
	const float ForwardValue = GetInputAxisValue("MoveForward");
	const float RightValue = GetInputAxisValue("MoveRight");

	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	MoveInDirection(MoveDirection, DeltaTime);
}

void ALDBasePawn::MoveInDirection(FVector MoveDirection, float DeltaTime)
{
	const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

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

void ALDBasePawn::UpdateCurrentTile(class ALDTile* Tile)
{
	this->LastTileHovered = this->CurrentTile;
	this->CurrentTile = Tile;
}


// Called to bind functionality to input
void ALDBasePawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward");
	InputComponent->BindAxis("MoveRight");
	InputComponent->BindAxis("ActionForward");
	InputComponent->BindAxis("ActionRight");
}

