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
	
	GetMainCamera();

	BindToInput();
}


// Called every frame
void UPortalGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Gets the camera component tagged with "MainCamera" attached to a capsule component.
void UPortalGun::GetMainCamera()
{
	TestComponent = this->GetOwner()->FindComponentByClass<UCapsuleComponent>();

	for (int i = 0; i < TestComponent->GetAttachChildren().Num(); i++)
	{
		if (TestComponent->GetAttachChildren()[i]->ComponentHasTag("MainCamera"))
		{
			MainCamera = Cast<UCameraComponent>(TestComponent->GetAttachChildren()[i]);
			break;
		}
	}
}

//Binds inputs allowing users to place portals.
void UPortalGun::BindToInput()
{
	UInputComponent* InputComponent = NewObject<UInputComponent>(this);
	InputComponent->BindAction("PlacePortal1", IE_Pressed, this, &UPortalGun::MovePortal1);
	InputComponent->BindAction("PlacePortal2", IE_Pressed, this, &UPortalGun::MovePortal2);
	InputComponent->BindAction("ExitGame", IE_Pressed, this, &UPortalGun::ExitGame);
}

//Function used to place and move portal1.
void UPortalGun::MovePortal1()
{
	if (MainCamera != NULL)
	{
		//Initalizes the line trace
		FHitResult OutHit;
		FVector Start = MainCamera->GetComponentLocation();

		FVector ForwardVector = MainCamera->GetForwardVector();
		FVector End((ForwardVector * 10000.f) + Start);
		FCollisionQueryParams CollisionParams;
		
		bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

		//Checks if there is an actor being hit by the line trace and if the actor hit is a portal wall.
		if (OutHit.GetActor() && OutHit.GetActor()->GetRootComponent()->ComponentHasTag("PortalWall"))
		{
			FActorSpawnParameters PortalSpawnParams;

			//Initalizes the location and rotation of portal1.
			const FVector MovePortal = OutHit.ImpactPoint;
			const FRotator RotatePortal = OutHit.GetActor()->GetActorRotation();

			if (isHit)
			{
				if (OutHit.bBlockingHit)
				{
					//Initalizes portal1 and spawns it into the scene if portal1 hasn't already been placed.
					if (!Portal1Placed)
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));

						APortal* PortalSpawner = GetWorld()->SpawnActor<APortal>(Portal1_BP, MovePortal, RotatePortal, PortalSpawnParams);
						Portal1 = PortalSpawner;

						//Checks if portal2 has been placed and if so, will then attach portal1 to portal2.
						if (Portal2Placed)
						{
							Portal1->OtherPortal = Portal2;
							Portal2->OtherPortal = Portal1;
						}

						Portal1Placed = true;
					}
					//If portal1 has already been placed, move it to current hit location.
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
						Portal1->TeleportTo(MovePortal, RotatePortal);
					}
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("You aren't hitting anything!")));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("No Main Camera found!")));
	}
}

//Function used to place and move portal2.
void UPortalGun::MovePortal2()
{
	if (MainCamera != NULL)
	{
		//Initalizes the line trace
		FHitResult OutHit;
		FVector Start = MainCamera->GetComponentLocation();

		FVector ForwardVector = MainCamera->GetForwardVector();
		FVector End((ForwardVector * 10000.f) + Start);
		FCollisionQueryParams CollisionParams;

		bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

		//Checks if the Actor hit by the line trace is a portal wall.
		if (OutHit.GetActor() && OutHit.GetActor()->GetRootComponent()->ComponentHasTag("PortalWall"))
		{
			FActorSpawnParameters PortalSpawnParams;

			//Initalizes the location and rotation of portal2.
			const FVector MovePortal = OutHit.ImpactPoint;
			const FRotator RotatePortal = OutHit.GetActor()->GetActorRotation();

			if (isHit)
			{
				if (OutHit.bBlockingHit)
				{
					//Initalizes portal2 and spawns it into the scene if portal2 hasn't already been placed.
					if (!Portal2Placed)
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
						APortal* PortalSpawner = GetWorld()->SpawnActor<APortal>(Portal2_BP, MovePortal, RotatePortal, PortalSpawnParams);
						Portal2 = PortalSpawner;

						//Checks if portal1 has been placed and if so, will then attach portal2 to portal1.
						if (Portal1Placed)
						{
							Portal2->OtherPortal = Portal1;
							Portal1->OtherPortal = Portal2;
						}

						Portal2Placed = true;
					}
					//If portal has already been placed, move it to current hit location.
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
						Portal2->TeleportTo(MovePortal, RotatePortal);
					}
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("You aren't hitting anything!")));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("No Main Camera found!")));
	}
}

void UPortalGun::ExitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}
