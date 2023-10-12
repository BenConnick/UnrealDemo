// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmPlayerController.h"

#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NoteBar.h"
#include "Rhythm.h"


// Sets default values
ARhythmPlayerController::ARhythmPlayerController()
	: APlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARhythmPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	for(TActorIterator<ANoteBar> It(GetWorld()); It; ++It)
	{
		NoteBar = *It;
		break;
	}

	if (!NoteBar)
	{
		LoudError(TEXT("WARNING: Must have a NoteBar in the World"));
	}
}

void ARhythmPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// bind input
		for (int i = 0; i < BeatHitActions.Num(); ++i)
		{
			UInputAction* beatHitAction = BeatHitActions[i];
			EnhancedInputComponent->BindAction(beatHitAction, ETriggerEvent::Started, this, &ARhythmPlayerController::OnBeatHitStarted, i);
			EnhancedInputComponent->BindAction(beatHitAction, ETriggerEvent::Completed, this, &ARhythmPlayerController::OnBeatHitReleased, i);
		}
	}
	else
	{
		UE_LOG(LogRhythm, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ARhythmPlayerController::OnBeatHitStarted(int index)
{
	LoudError(FString::Printf(TEXT("BEAT HIT TRIGGERED %d"), index));

	if (NoteBar) NoteBar->TryHit(index);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ARhythmPlayerController::OnBeatHitReleased(int index)
{
	LoudError(FString::Printf(TEXT("BEAT HIT RELEASED %d"), index));
}

// Called every frame
void ARhythmPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

