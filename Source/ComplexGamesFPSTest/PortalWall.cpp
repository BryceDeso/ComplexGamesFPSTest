// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalWall.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APortalWall::APortalWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->AttachTo(Collider);
	Arrow->SetArrowColor(FColor::White);
	FQuat LocalArrowRotation = FQuat(FRotator(GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z));
	Arrow->AddLocalRotation(LocalArrowRotation);
}

// Called when the game starts or when spawned
void APortalWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

