// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "CleanerSpace.h"


// Sets default values
ACleanerSpace::ACleanerSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

