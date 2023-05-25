// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/BlasterTeamsGameMode.h"
#include "CTFGameMode.generated.h"

class AFlag;
class AFlagZone;
/**
 * 
 */
UCLASS()
class BLASTER_API ACTFGameMode : public ABlasterTeamsGameMode
{
	GENERATED_BODY()

public:
	virtual void PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController) override;
	void FlagCaptured(AFlag* Flag, AFlagZone* Zone);
};
