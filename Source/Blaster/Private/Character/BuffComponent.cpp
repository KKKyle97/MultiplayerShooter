// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BuffComponent.h"

#include "Character/BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HealRampUp(DeltaTime);
}

void UBuffComponent::Heal(float HealAmount, float HealingTime)
{
	bHealing = true;
	HealingRate = HealAmount / HealingTime;
	AmountToHeal += HealAmount;
}

void UBuffComponent::HealRampUp(float DeltaTime)
{
	if (!bHealing || !BlasterCharacter || BlasterCharacter->IsElimmed()) return;

	const float HealThisFrame = HealingRate * DeltaTime;
	BlasterCharacter->SetHealth(FMath::Clamp(BlasterCharacter->GetHealth() + HealThisFrame, 0.f, BlasterCharacter->GetMaxHealth()));
	BlasterCharacter->UpdateHUDHealth();
	AmountToHeal -= HealThisFrame;

	if (AmountToHeal <= 0 || BlasterCharacter->GetHealth() >= BlasterCharacter->GetMaxHealth())
	{
		bHealing = false;
		AmountToHeal = 0.f;
	}
}

void UBuffComponent::SetInitialSpeeds(float BaseSpeed, float CrouchSpeed)
{
	InitialBaseSpeed = BaseSpeed;
	InitialCrouchSpeed = CrouchSpeed;
}

void UBuffComponent::SetInitialJumpVelocity(float Velocity)
{
	InitialJumpVelocity = Velocity;
}

void UBuffComponent::BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float BuffTime)
{
	if (!BlasterCharacter) return;
	BlasterCharacter->GetWorldTimerManager().SetTimer(
		SpeedBuffTimer,
		this,
		&UBuffComponent::ResetSpeeds,
		BuffTime
	);

	if (BlasterCharacter->GetCharacterMovement())
	{
		BlasterCharacter->GetCharacterMovement()->MaxWalkSpeed = BuffBaseSpeed;
		BlasterCharacter->GetCharacterMovement()->MaxWalkSpeedCrouched = BuffCrouchSpeed;
	}
	MulticastSpeedBuff(BuffBaseSpeed, BuffCrouchSpeed);
}

void UBuffComponent::ResetSpeeds()
{
	if (!BlasterCharacter || !BlasterCharacter->GetCharacterMovement()) return;

	BlasterCharacter->GetCharacterMovement()->MaxWalkSpeed = InitialBaseSpeed;
	BlasterCharacter->GetCharacterMovement()->MaxWalkSpeedCrouched = InitialCrouchSpeed;
	MulticastSpeedBuff(InitialBaseSpeed, InitialCrouchSpeed);
}

void UBuffComponent::MulticastSpeedBuff_Implementation(float BaseSpeed, float CrouchSpeed)
{
	if (BlasterCharacter && BlasterCharacter->GetCharacterMovement())
	{
		BlasterCharacter->GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
		BlasterCharacter->GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	}
}

void UBuffComponent::BuffJump(float BuffJumpVelocity, float BuffTime)
{
	if (!BlasterCharacter) return;
	BlasterCharacter->GetWorldTimerManager().SetTimer(
		JumpBuffTimer,
		this,
		&UBuffComponent::ResetJump,
		BuffTime
	);

	if (BlasterCharacter->GetCharacterMovement())
	{
		BlasterCharacter->GetCharacterMovement()->JumpZVelocity = BuffJumpVelocity;
	}
	MulticastJumpBuff(BuffJumpVelocity);
}

void UBuffComponent::ResetJump()
{
	if (BlasterCharacter && BlasterCharacter->GetCharacterMovement())
	{
		BlasterCharacter->GetCharacterMovement()->JumpZVelocity = InitialJumpVelocity;
	}
	MulticastJumpBuff(InitialJumpVelocity);

}

void UBuffComponent::MulticastJumpBuff_Implementation(float BuffJumpVelocity)
{
	if (BlasterCharacter && BlasterCharacter->GetCharacterMovement())
	{
		BlasterCharacter->GetCharacterMovement()->JumpZVelocity = BuffJumpVelocity;
	}
}



