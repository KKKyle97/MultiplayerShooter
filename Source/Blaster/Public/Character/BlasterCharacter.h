// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurningInPlace.h"
#include "Blaster/Interface/BlasterDamagableInterface.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/CombatState.h"
#include "BlasterCharacter.generated.h"

class UBuffComponent;
class ABlasterPlayerState;
class ABlasterPlayerController;
class UCombatComponent;
class AWeapon;
class UCameraComponent;
class USpringArmComponent;
class UWidgetComponent;
class USoundCue;
UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter, public IBlasterDamagableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlasterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	void PlayFireMontage(bool bIsAiming);
	void PlayReloadMontage();
	void PlayElimMontage();
	void PlayHitReactMontage();
	void PlayThrowGrenadeMontage();
	void Elim();
	void UpdateHUDHealth();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastElim();
	virtual void OnRep_ReplicatedMovement() override;
	virtual void Destroyed() override;

	UPROPERTY(Replicated)
	bool bDisableGameplay = false;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowSniperScopeWidget(bool bShowScope);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void Lookup(float Value);
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void ReloadButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void CalculateAO_Pitch();
	float CalculateSpeed();
	void AimOffSet(float DeltaSeconds);
	void SimProxiesTurn();
	void FireButtonPressed();
	void FireButtonReleased();
	void GrenadeButtonPressed();

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* ControllerInstigator, AActor* DamageCauser);
	void PollInit();
	void RotateInPlace(float DeltaTime);
	virtual void Jump() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = "OnRep_CharacterWeapon")
	AWeapon* CharacterWeapon;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraThreshold = 300.f;

	UFUNCTION()
	void OnRep_CharacterWeapon(AWeapon* LastWeapon);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = true))
	UCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere)
	UBuffComponent* BuffComponent;

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaSeconds);

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* FireWeaponMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* ElimMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* ThrowGrenadeMontage;

	void HideCameraIfCharacterIsClose();

	bool bRotateRootBone;
	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float TimeSinceLastMovementReplicated;

	/*
	 * Player Health
	 */

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing=OnRep_Health, VisibleAnywhere, Category = "Player Stats")
	float Health = 100.f;

	UFUNCTION()
	void OnRep_Health(float LastHealth);

	UPROPERTY()
	ABlasterPlayerController* BlasterPlayerController;


	/*
	 * Elimination
	 */

	bool bElimmed = false;

	FTimerHandle ElimTimer;

	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;

	void ElimTimerFinished();

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolveTimeline;
	FOnTimelineFloat DissolveTrack;

	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);
	void StartDissolve();

	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveCurve;

	UPROPERTY(VisibleAnywhere, Category = Elim)
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, Category = Elim)
	UMaterialInstance* DissolveMaterialInstance;

	/*
	 * Elim bot
	 */

	UPROPERTY(EditAnywhere)
	UParticleSystem* ElimBotEffect;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ElimBotComponent;

	UPROPERTY(EditAnywhere)
	USoundCue* ElimBotSound;

	UPROPERTY()
	ABlasterPlayerState* BlasterPlayerState;

	/**
	 * Grenade
	 **/

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AttachedGrenade;

public:
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsWeaponEquipped();
	bool IsAiming();
	FORCEINLINE float GetAO_Yaw() { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() { return AO_Pitch; }
	FORCEINLINE ETurningInPlace GetTurningInplace() { return TurningInPlace; }
	FVector GetHitTarget();
	AWeapon* GetEquippedWeapon();
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return CameraComponent; }
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }
	FORCEINLINE bool IsElimmed() const { return bElimmed; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void SetHealth(float Amount) { Health = Amount; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	ECombatState GetCombatState();
	FORCEINLINE UCombatComponent* GetCombatComponent() { return CombatComponent; }
	FORCEINLINE bool GetDisableGameplay() const { return bDisableGameplay; }
	FORCEINLINE UAnimMontage* GetReloadMontage() const { return ReloadMontage; }
	FORCEINLINE UStaticMeshComponent* GetAttachedGrenade() const { return AttachedGrenade; }
	FORCEINLINE UBuffComponent* GetBuffComponent() const { return BuffComponent; }
};
