// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "LDSharedCamera.h"


// Sets default values
ALDSharedCamera::ALDSharedCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bDoCollisionTest = true;
	SpringArm->bAbsoluteRotation = true;
	SpringArm->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 800.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;

	RootComponent = SpringArm;
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ALDSharedCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALDSharedCamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FVector tmp;
	for (APawn* Pawn : WatchedPlayers)
	{
		if(Pawn)
			tmp += Pawn->GetActorLocation();
	}
	tmp /= WatchedPlayers.Num();
	tmp.Z = 200.f;
	SetActorLocation(tmp);
}

