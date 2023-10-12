// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteBar.h"
#include "NoteNib.h"
#include "Kismet/KismetMathLibrary.h"
#include "Rhythm/Rhythm.h"


// Sets default values
ANoteBar::ANoteBar()
  : Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
}

// Called when the game starts or when spawned
void ANoteBar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANoteBar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector normalizedToVector = EndPointWorldSpace - SpawnPointWorldSpace;
	normalizedToVector.Normalize();

	FVector rightVector = normalizedToVector.Cross(FVector::UpVector) * LaneWidth;

	double RemainingDelta = DeltaTime;
	while (TimeToNextSpawn < RemainingDelta)
	{
		RemainingDelta -= TimeToNextSpawn;
		TimeToNextSpawn = SpawnInterval;
		UClass* ToSpawn = NoteNibClass;
		if (ToSpawn != nullptr)
		{
			int laneIndex = FMath::RandRange(0,2);
			//for (int laneIndex = -1; laneIndex < 2; ++laneIndex)
			{
				ANoteNib* newNote = GetWorld()->SpawnActor<ANoteNib>(ToSpawn,
				SpawnPointWorldSpace + (rightVector * (laneIndex-1)) + normalizedToVector * (RemainingDelta * NoteSpeed),
				normalizedToVector.Rotation());
				newNote->Lane = laneIndex;
				ActiveNibs.Add(newNote);
			}
		}
		else
		{
			LoudError(FString::Printf(TEXT("No class set for ANoteBar::NoteNibClass on actor %s"), *GetName()), reinterpret_cast<uint64>(this));
		}
	}
	TimeToNextSpawn -= RemainingDelta;
	ensure(TimeToNextSpawn >= 0);
	
	FVector locationDelta = normalizedToVector * (DeltaTime * NoteSpeed);
	for (ANoteNib* noteNib : ActiveNibs)
	{
		if (IsValid(noteNib))
		{
			noteNib->SetActorLocation(noteNib->GetActorLocation() + locationDelta);
		}
	}

	while (ActiveNibs.Num() > 0)
	{
		ANoteNib* nib = ActiveNibs[0];
		if (IsValid(nib))
		{
			FVector toEnd = nib->GetActorLocation() - EndPointWorldSpace;
			if (toEnd.Dot(normalizedToVector) < 0)
			{
				break;
			}
			nib->Destroy();
		}
		ActiveNibs.RemoveAt(0);
	}
}

void ANoteBar::TryHit(int laneIndex)
{
	FVector toVector = EndPointWorldSpace - SpawnPointWorldSpace;
	FVector normalizedToVector = toVector;
	normalizedToVector.Normalize();

	for (int i = ActiveNibs.Num()-1; i >= 0; --i)
	{
		ANoteNib* nib = ActiveNibs[i];
		
		if (!IsValid(nib)) continue;
		
		if (nib->Lane != laneIndex) continue;

		FVector location = nib->GetActorLocation();

		double distanceFromPerfect = (location - PerfectHitPointWorldSpace).Dot(normalizedToVector);
		if (FMath::Abs(distanceFromPerfect) < AcceptableHitDistanceWorldSpace)
		{
			// hit!
			LoudError(FString::Printf(TEXT("Hit! Lane: %d, Distance: %f"), nib->Lane, distanceFromPerfect), reinterpret_cast<uint64>(this));
			
			// remove
			ActiveNibs.RemoveAt(i);
			nib->Destroy();
		}
	}
}

