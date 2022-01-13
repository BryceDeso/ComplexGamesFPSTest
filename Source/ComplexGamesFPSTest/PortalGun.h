// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Portal.h"
#include "PortalGun.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMPLEXGAMESFPSTEST_API UPortalGun : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPortalGun();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void BindToInput();

	void MovePortal1();
	void MovePortal2();

	UPROPERTY(AdvancedDisplay, EditAnywhere)
	TSubclassOf<APortal> Portal1;
	UPROPERTY(AdvancedDisplay, EditAnywhere)
	TSubclassOf<APortal> Portal2;

	APortal* CurrentPortal1;
	APortal* CurrentPortal2;

	UPROPERTY(AdvancedDisplay, EditAnywhere)
	UCameraComponent* MainCamera;

	UPROPERTY(AdvancedDisplay, EditAnywhere)
	UCapsuleComponent* TestComponent;

	bool PortalPlaced1;
	bool PortalPlaced2;
};