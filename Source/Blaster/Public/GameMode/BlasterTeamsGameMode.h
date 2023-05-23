// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/BlasterGameMode.h"
#include "BlasterTeamsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterTeamsGameMode : public ABlasterGameMode
{
	GENERATED_BODY()

public:
	ABlasterTeamsGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual float CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage) override;
	virtual void PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController) override;
protected:
	virtual void HandleMatchHasStarted() override;
};
