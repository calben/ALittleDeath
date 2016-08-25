// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LDTile.generated.h"

UCLASS()
class ALITTLEDEATH_API ALDTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALDTile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
		bool bSelected = false;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* TileMaterialDamaging;

	UPROPERTY(EditAnywhere)
		bool bTileDamaging;

	UPROPERTY(EditAnywhere)
		bool bTileBlocked;

	UPROPERTY(EditAnywhere)
		class ALDArena* Arena;

	UPROPERTY(EditAnywhere)
		float TileDamagePerSecond = 99999999.0f;

	UPROPERTY(EditAnywhere)
		int ArenaX;

	UPROPERTY(EditAnywhere)
		int ArenaY;

	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetTileDamaging(bool ShouldDamage, float DPS = 999999999.0f);

	TArray<ALDTile*> GetAdjacentTiles();
};
