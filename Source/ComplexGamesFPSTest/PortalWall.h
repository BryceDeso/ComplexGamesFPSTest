// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalWall.generated.h"

UCLASS()
class COMPLEXGAMESFPSTEST_API APortalWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalWall();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent* Arrow;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
