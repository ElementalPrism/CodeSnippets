// Fill out your copyright notice in the Description page of Project Settings.


#include "BetterGameProject/Puzzles/WireBlockTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "GrabbableWire.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWireBlockTrigger::AWireBlockTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionArea->SetBoxExtent(BoxSize);
	CollisionArea->SetCollisionProfileName("Trigger");
	RootComponent = CollisionArea;

	CollisionArea->OnComponentBeginOverlap.AddDynamic(this, &AWireBlockTrigger::OnComponentOverLapStart);

}

// Called when the game starts or when spawned
void AWireBlockTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWireBlockTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWireBlockTrigger::OnComponentOverLapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	switch(BoxCheck)
	{
	case CheckForTheFollowingBox::Red:


		if ((OtherActor->ActorHasTag("WireBlock")) && (OtherActor->ActorHasTag("Red")))
		{
			//IsSocketed = true;
			//OtherActor->SetActorLocation(AreaClamp); //Attachs Cog to Area Defined
			//OtherComp->SetWorldLocation(AreaClamp); //Attachs Cog to Area Defined
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, "Clamped");
			OtherActor->SetActorRotation(ResetRotation); //resets the rotatation of Cog

			AGrabbableWire* Wire = Cast<AGrabbableWire>(OtherActor); //Casts the otheractor as a wire

			if (Wire)
			{
				Wire->Clamp = AreaClamp;
				Wire->NewClampSpeed = ClampSpeed;
				Wire->IsMoving = true;
				OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Stops Collision and physics when the cog enters the area required.
			}


		}

		if((OtherActor->ActorHasTag("WireBlock")) && (!OtherActor->ActorHasTag("Red")))
		{
			if (IncorrectSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), IncorrectSound, SoundVolume, Pitch, SoundStartTime);
			}
		}

		break;
	case CheckForTheFollowingBox::Blue:


		if ((OtherActor->ActorHasTag("WireBlock")) && (OtherActor->ActorHasTag("Blue")))
		{
			//IsSocketed = true;
			//OtherActor->SetActorLocation(AreaClamp); //Attachs Cog to Area Defined
			//OtherComp->SetWorldLocation(AreaClamp); //Attachs Cog to Area Defined
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, "Clamped");
			OtherActor->SetActorRotation(ResetRotation); //resets the rotatation of Cog

			AGrabbableWire* Wire = Cast<AGrabbableWire>(OtherActor); //Casts the otheractor as a wire

			if (Wire)
			{
				Wire->Clamp = AreaClamp;
				Wire->NewClampSpeed = ClampSpeed;
				Wire->IsMoving = true;
				OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Stops Collision and physics when the cog enters the area required.
			}


		}


		if ((OtherActor->ActorHasTag("WireBlock")) && (!OtherActor->ActorHasTag("Blue")))
		{
			if (IncorrectSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), IncorrectSound, SoundVolume, Pitch, SoundStartTime);
			}
		}

		break;
	case CheckForTheFollowingBox::Yellow:


		if ((OtherActor->ActorHasTag("WireBlock")) && (OtherActor->ActorHasTag("Yellow")))
		{
			//IsSocketed = true;
			//OtherActor->SetActorLocation(AreaClamp); //Attachs Cog to Area Defined
			//OtherComp->SetWorldLocation(AreaClamp); //Attachs Cog to Area Defined
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, "Clamped");
			OtherActor->SetActorRotation(ResetRotation); //resets the rotatation of Cog

			AGrabbableWire* Wire = Cast<AGrabbableWire>(OtherActor); //Casts the otheractor as a wire

			if (Wire)
			{
				Wire->Clamp = AreaClamp;
				Wire->NewClampSpeed = ClampSpeed;
				Wire->IsMoving = true;
				OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Stops Collision and physics when the cog enters the area required.
			}


		}

		if ((OtherActor->ActorHasTag("WireBlock")) && (!OtherActor->ActorHasTag("Yellow")))
		{
			if (IncorrectSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), IncorrectSound, SoundVolume, Pitch, SoundStartTime);
			}
		}

		break;
	default:

		break;
	}







	//if (OtherActor->ActorHasTag("WireBlock"))
	//{
	//	IsSocketed = true;
	//	OtherActor->SetActorLocation(AreaClamp); //Attachs Cog to Area Defined
	//	OtherComp->SetWorldLocation(AreaClamp); //Attachs Cog to Area Defined
	//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, "Clamped");
	//	OtherActor->SetActorRotation(ResetRotation); //resets the rotatation of Cog

	//	AGrabbableWire* Wire = Cast<AGrabbableWire>(OtherActor); //Casts the otheractor as a wire

	//	if (Wire)
	//	{
	//		OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Stops Collision and physics when the cog enters the area required.
	//	}


	//}

}

void AWireBlockTrigger::OnComponentOverLapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("WireBlock"))
	{
		IsSocketed = false;
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, "Left Trigger");
	}
}

bool AWireBlockTrigger::GetIsSocketed()
{
	return IsSocketed; //returns if the cog is socketed.
}
