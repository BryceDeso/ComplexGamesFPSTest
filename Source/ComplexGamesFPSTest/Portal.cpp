// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"
#include "Math/Quat.h"
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
				FRotator OldRotation = FRotator(0.0f, Other->GetActorForwardVector().Z, 0.0f);
				FRotator NewRotation = FRotator(0.0f, OtherPortal->GetActorRotation().Yaw, 0.0f);

				

				if (Cast<ACharacter>(Other))
				{
					TestChar = Cast<ACharacter>(Other);
					Other->TeleportTo(OtherPortal->GetActorLocation(), NewRotation, false, true);
					TestChar->GetController()->SetControlRotation(NewRotation);
				}
				else
				{
					Other->TeleportTo(OtherPortal->GetActorLocation(), OldRotation, false, true);
				}
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