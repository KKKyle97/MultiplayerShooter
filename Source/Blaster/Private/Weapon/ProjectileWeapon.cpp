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
	UWorld* World = GetWorld();

    if (MuzzleFlashSocket && World)
    {
        FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
        FVector ToTarget = HitTarget - SocketTransform.GetLocation();
        FRotator TargetRotation = ToTarget.Rotation();

    	FActorSpawnParameters SpawnParameters;
    	SpawnParameters.Owner = GetOwner();
    	SpawnParameters.Instigator = InstigatorPawn;

    	AProjectile* SpawnedProjectile = nullptr;

    	if (bUseServerSideRewind)
    	{
    		if (InstigatorPawn->HasAuthority()) // Server
    		{
    			if (InstigatorPawn->IsLocallyControlled()) // server, host - use replicated projectile
    			{
    				SpawnedProjectile = World->SpawnActor<AProjectile>(ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParameters);
    				SpawnedProjectile->bUseServerSideRewind = false;
    				SpawnedProjectile->Damage = FireDamage;
    			}
                else // server, not locally controlled - spawn non-replicated projectile, SSR
                {
                	SpawnedProjectile = World->SpawnActor<AProjectile>(ServerSideRewindProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParameters);
                	SpawnedProjectile->bUseServerSideRewind = true;
                }
    		}
            else // client, using SSR
            {
	            if (InstigatorPawn->IsLocallyControlled()) // client, locally controlled - spawn non-replicated projectile, use SSR
	            {
	            	SpawnedProjectile = World->SpawnActor<AProjectile>(ServerSideRewindProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParameters);
					SpawnedProjectile->bUseServerSideRewind = true;
	            	SpawnedProjectile->TraceStart = SocketTransform.GetLocation();
	            	SpawnedProjectile->InitialVelocity = SpawnedProjectile->GetActorForwardVector() * SpawnedProjectile->InitialSpeed;
	            	SpawnedProjectile->Damage = FireDamage;
	            }
	            else // client, not locally controlled - spawn non-replicated projectile, no SSR
	            {
	            	SpawnedProjectile = World->SpawnActor<AProjectile>(ServerSideRewindProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParameters);
	            	SpawnedProjectile->bUseServerSideRewind = false;
	            }
            }
    	}
    	else // weapon not using SSR
    	{
			if (InstigatorPawn->HasAuthority())
			{
				SpawnedProjectile = World->SpawnActor<AProjectile>(ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParameters);
				SpawnedProjectile->bUseServerSideRewind = false;
				SpawnedProjectile->Damage = FireDamage;
			}
    	}
	}
}
