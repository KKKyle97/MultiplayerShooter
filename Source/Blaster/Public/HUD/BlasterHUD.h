// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"

class UElimAnnoucement;
class UAnnouncement;
class UCharacterOverlay;
USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UTexture2D* CrosshairsCenter;

	UPROPERTY()
	UTexture2D* CrosshairsLeft;

	UPROPERTY()
	UTexture2D* CrosshairsRight;

	UPROPERTY()
	UTexture2D* CrosshairsTop;

	UPROPERTY()
	UTexture2D* CrosshairsBottom;
	float CrosshairSpread;
	FLinearColor CrosshairColor;
};
/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<class UUserWidget> CharacterOverlayClass;
	void AddCharacterOverlay();


	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;

	UPROPERTY(EditAnywhere, Category = "Announcements")
	TSubclassOf<UUserWidget> AnnouncementClass;

	UPROPERTY()
	UAnnouncement* Announcement;

	void AddAnnouncement();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UElimAnnoucement> ElimAnnouncementClass;

	void AddElimAnnouncement(FString Attacker, FString Victim);

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	float ElimAnnouncementTime = 2.5f;

	UFUNCTION()
	void ElimAnnouncementTimerFinished(UElimAnnoucement* MsgToRemove);

	UPROPERTY()
	TArray<UElimAnnoucement*> ElimMessages;

	FHUDPackage HUDPackage;

	UPROPERTY()
	APlayerController* OwningPlayer;

	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairColor);

	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 16.f;
public:
		FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) { HUDPackage = Package; }
};
