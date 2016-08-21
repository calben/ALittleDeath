// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpawningUtils.generated.h"

/**
 * 
 */
UCLASS()
class ALITTLEDEATH_API USpawningUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = SpawnUtil)
		static void SpawnArenaBorders(UObject* WorldContextObject, FVector ArenaDimensions);
	
};
