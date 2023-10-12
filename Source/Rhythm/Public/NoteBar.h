// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteBar.generated.h"

class ANoteNib;

UCLASS()
class RHYTHM_API ANoteBar : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANoteBar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TryHit(int laneIndex);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ANoteNib> NoteNibClass;

	UPROPERTY(Transient, BlueprintReadWrite)
	TArray<ANoteNib*> ActiveNibs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double LaneWidth = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnPointWorldSpace;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPointWorldSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PerfectHitPointWorldSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double AcceptableHitDistanceWorldSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double NoteSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double SpawnInterval;

	UPROPERTY(Transient, BlueprintReadWrite)
	double TimeToNextSpawn = 0;
};
