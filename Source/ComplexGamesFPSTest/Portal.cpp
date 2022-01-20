// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"

// Sets default values
APortal::APortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetGenerateOverlapEvents(true);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->AttachTo(Collider);
	Arrow->SetArrowColor(FColor::White);
	FQuat LocalArrowRotation = FQuat(FRotator(GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z));
	Arrow->AddLocalRotation(LocalArrowRotation);

	PortalActive = true;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &APortal::TeleportObject);
	Collider->OnComponentEndOverlap.AddDynamic(this, &APortal::ReActivatePortal);
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PortalActive == false)
	{
		this->Collider->SetActive(false);
	}
	else
	{
		this->Collider->SetActive(true);
	}
}

//Teleports an object to the OtherPortal's location if it collides with this portal's collider.
void APortal::TeleportObject(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherPortal)
	{
		if ((Other != NULL) && (Other != this))
		{
			if (Other->GetRootComponent()->ComponentHasTag("PortableObject") && PortalActive == true)
			{
				OtherPortal->PortalActive = false;
				FRotator NewRotation = FRotator(0.0f, OtherPortal->GetActorRotation().Yaw, 0.0f);

				if (Cast<ACharacter>(Other))
				{
					TestChar = Cast<ACharacter>(Other);
					Other->SetActorLocation(OtherPortal->GetActorLocation());
					TestChar->GetController()->SetControlRotation(NewRotation);
				}
				else
				{
					Other->TeleportTo(OtherPortal->GetActorLocation(), NewRotation, false, true);
				}
			}
		}
	}
}

//After an object teleports and exits it's collider, will then set PortalActive to true.
void APortal::ReActivatePortal(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Other->GetRootComponent()->ComponentHasTag("PortableObject"))
	{
		PortalActive = true;
	}
}