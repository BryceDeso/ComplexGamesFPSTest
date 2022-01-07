// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"

// Sets default values
APortal::APortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetGenerateOverlapEvents(true);

	PortalActive = true;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &APortal::TeleportPlayer);
	Collider->OnComponentEndOverlap.AddDynamic(this, &APortal::EndOverlap);
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

void APortal::TeleportPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherPortal)
	{
		if ((Other != NULL) && (Other != this))
		{
			if (Other->GetRootComponent()->ComponentHasTag("PortableObject") && PortalActive == true)
			{
				OtherPortal->PortalActive = false;
				Other->TeleportTo(OtherPortal->GetActorLocation(), Other->GetActorRotation(), false, false);
			}
		}
	}
}

void APortal::EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Other->GetRootComponent()->ComponentHasTag("PortableObject"))
	{
		PortalActive = true;
	}
}