// Fill out your copyright notice in the Description page of Project Settings.


#include "GearBoxTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BetterGameProject/Grabbables/Cog.h"
#include "Engine/Engine.h"

// Sets default values
AGearBoxTrigger::AGearBoxTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionArea->SetBoxExtent(BoxSize);
	CollisionArea->SetCollisionProfileName("Trigger");
	RootComponent = CollisionArea;

	CollisionArea->OnComponentBeginOverlap.AddDynamic(this, &AGearBoxTrigger::OnComponentOverLapStart);


}

// Called when the game starts or when spawned
void AGearBoxTrigger::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AGearBoxTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(DoneLerping == true)
	{
		IsSocketed = true;
		DoneLerping = false;

		if (LogOnly == true)
		{
			CogPass->SetMobility(EComponentMobility::Stationary);
			ClampStop = true;
			LogPrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			UGameplayStatics::PlaySound2D(GetWorld(), PassageAvailable, SoundVolume, SoundPitch, SoundStartTime);
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Regain Physics");
			//CogPass->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			
		}

	}

}

void AGearBoxTrigger::OnComponentOverLapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor->ActorHasTag("Cog")) && (ClampStop == false))
	{
		//IsSocketed = true;

		//OtherActor->SetActorLocation(FMath::Lerp(this->GetActorLocation(), AreaClamp, ClampSpeed));
		//OtherActor->SetActorLocation(AreaClamp); //Attachs Cog to Area Defined
		//OtherComp->SetWorldLocation(AreaClamp); //Attachs Cog to Area Defined
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, "Clamped");
		OtherActor->SetActorRotation(ResetRotation); //resets the rotatation of Cog
		
		ACog* Cog = Cast<ACog>(OtherActor); //Casts the otheractor as a cog
		
		if (Cog)
		{
			Cog->Clamp = AreaClamp;

			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, "SpinActivated");

			if ((Cog->IsLog == false) && (LogOnly == false))
			{
				Cog->NewClampSpeed = ClampSpeed;
				Cog->GearBox = this;
				Cog->IsMoving = true;
				OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
			}

			if ((Cog->IsLog) && (LogOnly == true))
			{
				//OtherActor->SetActorLocation(AreaClamp)
				Cog->NewClampSpeed = ClampSpeed;
				Cog->GearBox = this;
				LogPrimitiveComponent = OtherComp;
				Cog->IsMoving = true;
				OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

				//OtherComp->SetMobility(EComponentMobility::Stationary);
			}
			//Stops Collision and physics when the cog enters the area required.
			//Cog->IsSpinning = true;  //activates spinning
		}



	}

}

void AGearBoxTrigger::OnComponentOverLapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Cog"))
	{
		IsSocketed = false;
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, "Left Trigger");
	}
}

bool AGearBoxTrigger::GetIsSocketed()
{
	return IsSocketed; //returns if the cog is socketed.
}

	
