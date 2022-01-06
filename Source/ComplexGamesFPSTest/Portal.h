// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class COMPLEXGAMESFPSTEST_API APortal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APortal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* Collider;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void TeleportPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
		bool PortalActive;

	UPROPERTY(AdvancedDisplay, EditAnywhere)
		APortal* OtherPortal;

};
