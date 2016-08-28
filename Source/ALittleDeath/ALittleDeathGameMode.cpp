// Fill out your copyright notice in the Description page of Project Settings.

#include "ALittleDeath.h"
#include "Player/LDPlayerPawn.h"
#include "Player/LDSharedCamera.h"
#include "ALittleDeathGameMode.h"

AALittleDeathGameMode::AALittleDeathGameMode()
{
	DefaultPawnClass = ALDPlayerPawn::StaticClass();
}

void AALittleDeathGameMode::BeginPlay()
{
	UGameplayStatics::CreatePlayer(GetWorld(), 1);
	ALDSharedCamera* SharedCamera = GetWorld()->SpawnActor<ALDSharedCamera>(FVector(0.f, 0.f, 10000.f), FRotator::ZeroRotator);
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* Controller = Cast<APlayerController>(*Iterator);
		if (Controller)
		{
			if (!Controller->IsLocalController())
			{
				UE_LOG(LogTemp, Warning, TEXT("DETECTED NONLOCAL CONTROLLER"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("DETECTED LOCAL CONTROLLER %s"), *Controller->GetName());
				if(SharedCamera)
					SharedCamera->WatchedPlayers.Add(Controller->GetPawn());
			}
		}
	}
	if(SharedCamera)
		GetWorld()->GetFirstPlayerController()->SetViewTarget(SharedCamera);
}