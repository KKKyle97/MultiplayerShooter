// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/JumpPickup.h"

#include "Character/BlasterCharacter.h"
#include "Character/BuffComponent.h"

void AJumpPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, HitResult);

	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter)
	{
		UBuffComponent* BuffComponent = BlasterCharacter->GetBuffComponent();
		if (BuffComponent)
		{
			BuffComponent->BuffJump(JumpZVelocityBuff, JumpBuffTime);
		}
	}

	Destroy();
}
