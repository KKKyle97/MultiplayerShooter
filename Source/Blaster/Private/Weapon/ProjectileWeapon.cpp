// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ProjectileWeapon.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Weapon/Projectile.h"

void AProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	if (!HasAuthority()) return;

	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));

    if (MuzzleFlashSocket)
    {
        FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
        FVector ToTarget = HitTarget - SocketTransform.GetLocation();
        FRotator TargetRotation = ToTarget.Rotation();
        if (ProjectileClass && InstigatorPawn)
        {
            FActorSpawnParameters SpawnParameters;
            SpawnParameters.Owner = GetOwner();
            SpawnParameters.Instigator = InstigatorPawn;
            UWorld* World = GetWorld();
            if (World)
            {
				World->SpawnActor<AProjectile>(
					ProjectileClass,
					SocketTransform.GetLocation(),
					TargetRotation,
					SpawnParameters
				);
			}
		}
	}
}
