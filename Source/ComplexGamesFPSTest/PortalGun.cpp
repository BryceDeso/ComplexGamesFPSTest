// Fill out your copyright notice in the Description page of Project Settings.

#include "PortalGun.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Portal.h"

// Sets default values for this component's properties
UPortalGun::UPortalGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPortalGun::BeginPlay()
{
	Super::BeginPlay();

	TestComponent = this->GetOwner()->FindComponentByClass<UCapsuleComponent>();

	for (int i = 0; i < TestComponent->GetAttachChildren().Num(); i++)
	{
		if (TestComponent->GetAttachChildren()[i]->ComponentHasTag("MainCamera"))
		{
			MainCamera = Cast<UCameraComponent>(TestComponent->GetAttachChildren()[i]);
		}
	}
	

	BindToInput();
}


// Called every frame
void UPortalGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UPortalGun::BindToInput()
{
	UInputComponent* InputComponent = NewObject<UInputComponent>(this);
	InputComponent->BindAction("PlacePortal1", IE_Pressed, this, &UPortalGun::MovePortal1);
	InputComponent->BindAction("PlacePortal2", IE_Pressed, this, &UPortalGun::MovePortal2);
}

void UPortalGun::MovePortal1()
{
	if (MainCamera != NULL)
	{
		FHitResult OutHit;
		FVector Start = MainCamera->GetComponentLocation();

		FVector ForwardVector = MainCamera->GetForwardVector();
		FVector End((ForwardVector * 1000.f) + Start);
		FCollisionQueryParams CollisionParams;

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);

		bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

		FActorSpawnParameters PortalSpawnParams;

		const FVector MovePortal = OutHit.ImpactPoint;
		/*const FRotator RotatePortal = */

		if (isHit)
		{
			if (OutHit.bBlockingHit)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName())); \
					APortal* PortalSpawner = GetWorld()->SpawnActor<APortal>(Portal1, MovePortal, RotatePortal, PortalSpawnParams);
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("No Main Camera found!")));
	}
}

void UPortalGun::MovePortal2()
{
	if (MainCamera != NULL)
	{
		FHitResult OutHit;
		FVector Start = MainCamera->GetComponentLocation();

		FVector ForwardVector = MainCamera->GetForwardVector();
		FVector End((ForwardVector * 1000.f) + Start);
		FCollisionQueryParams CollisionParams;

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);

		bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

		FActorSpawnParameters PortalSpawnParams;

		const FVector MovePortal = OutHit.Location;
		const FRotator RotatePortal = OutHit.GetActor()->GetActorRotation();

		if (isHit)
		{
			if (OutHit.bBlockingHit)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
				APortal* PortalSpawner = GetWorld()->SpawnActor<APortal>(Portal2, MovePortal, RotatePortal, PortalSpawnParams);
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("No Main Camera found!")));
	}
}
