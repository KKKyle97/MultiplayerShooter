// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickupsSpawnPoint.h"

#include "Pickups/Pickup.h"

APickupsSpawnPoint::APickupsSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void APickupsSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	StartSpawnPickupTimer(nullptr);
}

void APickupsSpawnPoint::SpawnPickup()
{
	int32 NumPickupClasses = PickupClasses.Num();
	if (NumPickupClasses > 0)
	{
		int32 Selection = FMath::RandRange(0, NumPickupClasses - 1);
		SpawnedPickup =	GetWorld()->SpawnActor<APickup>(PickupClasses[Selection], GetActorTransform());

		if (HasAuthority() && SpawnedPickup)
		{
			SpawnedPickup->OnDestroyed.AddDynamic(this, &ThisClass::APickupsSpawnPoint::StartSpawnPickupTimer);
		}
	}
}

void APickupsSpawnPoint::SpawnPickupTimerFinished()
{
	if (HasAuthority())
	{
		SpawnPickup();
	}
}

void APickupsSpawnPoint::StartSpawnPickupTimer(AActor* DestroyedActor)
{
	const float SpawnTime = FMath::FRandRange(SpawnPickupTimeMin, SpawnPickupTimeMax);
	GetWorldTimerManager().SetTimer(
		SpawnPickupTimer,
		this,
		&APickupsSpawnPoint::SpawnPickupTimerFinished,
		SpawnTime
	);
}

void APickupsSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

