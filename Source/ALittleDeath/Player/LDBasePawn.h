// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "LDBasePawn.generated.h"

UCLASS()
class ALITTLEDEATH_API ALDBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALDBasePawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 300.0f;

	UPROPERTY(EditAnywhere)
		class ALDTile* LastTileHovered;

	UPROPERTY(EditAnywhere)
		class ALDTile* LastTileSelected;

	UPROPERTY(EditAnywhere)
		class ALDTile* CurrentTile;

	UPROPERTY(EditAnywhere)
		class APawnSpawningArea* SpawnPoint = nullptr;

	UPROPERTY(EditAnywhere)
		float AttackActionDelay = .2f;

	UPROPERTY(EditAnywhere)
		float PrimaryActionDelay = 1.f;

	UPROPERTY(EditAnywhere)
		float SecondaryActionDelay = 1.f;

	UPROPERTY(EditAnywhere)
		FVector LookDirection;

	UPROPERTY(EditAnywhere)
		FVector MoveDirection;

	float tmp_attack_action_timer;
	float tmp_primary_action_timer;
	float tmp_secondary_action_timer;

	void UpdateCurrentTile(class ALDTile* Tile);

	void MoveInDirection(FVector Direction, float DeltaTime);

	void FireProjectileInDirection(FVector Direction);

	virtual void DoAttackAction();

	virtual void DoPrimaryAction();

	virtual void DoSecondaryAction();

	virtual void Die();
};
