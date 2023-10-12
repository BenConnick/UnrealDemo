// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteNib.generated.h"

UCLASS()
class RHYTHM_API ANoteNib : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANoteNib();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
