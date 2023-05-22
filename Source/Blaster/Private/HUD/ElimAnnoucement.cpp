// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ElimAnnoucement.h"

#include "Components/TextBlock.h"

void UElimAnnoucement::SetElimAnnouncementText(FString AttackerName, FString VictimName)
{
	FString ElimAnnouncementText = FString::Printf(TEXT("%s elimmed %s!"), *AttackerName, *VictimName);

	if (AnnouncementText)
	{
		AnnouncementText->SetText(FText::FromString(ElimAnnouncementText));
	}
}
