// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/CTFGameMode.h"

#include "CaptureTheFlag/FlagZone.h"
#include "GameState/BlasterGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Flag.h"

void ACTFGameMode::PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController,
                                    ABlasterPlayerController* AttackerController)
{
	ABlasterGameMode::PlayerEliminated(ElimmedCharacter, VictimController, AttackerController);
}

void ACTFGameMode::FlagCaptured(AFlag* Flag, AFlagZone* Zone)
{
	bool bValidCapture = Flag->GetTeam() != Zone->Team;
	ABlasterGameState* BlasterGameState = Cast<ABlasterGameState>(UGameplayStatics::GetGameState(this));
	if (BlasterGameState)
	{
		if (Zone->Team == ETeam::ET_BlueTeam)
		{
			BlasterGameState->BlueTeamScores();
		}

		if (Zone->Team == ETeam::ET_RedTeam)
		{
			BlasterGameState->RedTeamScores();
		}
	}
}
