// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ComplexGamesFPSTestHUD.generated.h"

UCLASS()
class AComplexGamesFPSTestHUD : public AHUD
{
	GENERATED_BODY()

public:
	AComplexGamesFPSTestHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

