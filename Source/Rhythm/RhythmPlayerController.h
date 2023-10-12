// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RhythmPlayerController.generated.h"

class ANoteBar;
class UInputMappingContext;
class UInputAction;

UCLASS()
class RHYTHM_API ARhythmPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Sets default values for this actor's properties
	ARhythmPlayerController();

	/* MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/* Beat Hit Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TArray<UInputAction*> BeatHitActions;

	/* Note Bar */
	UPROPERTY(Transient, BlueprintReadWrite)
	ANoteBar* NoteBar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	void OnBeatHitStarted(int index);
	void OnBeatHitReleased(int index);
};
