// Fill out your copyright notice in the Description page of Project Settings.


#include "BetterGameProject/Puzzles/GrabbableWire.h"
#include "Kismet/GameplayStatics.h"

AGrabbableWire::AGrabbableWire()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGrabbableWire::BeginPlay()
{
	Super::BeginPlay();
}


void AGrabbableWire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsMoving == true)
	{
		SetActorLocation(FMath::Lerp(this->GetActorLocation(), Clamp, NewClampSpeed));
	}


	if ((FVector::Distance(GetActorLocation(), Clamp) < 5.0f) && (InsertSound))
	{
		if((BlockTrigger) && (BlockTriggerBlock == false))
		{
			BlockTrigger->IsSocketed = true;
			UGameplayStatics::PlaySound2D(GetWorld(), InsertSound, SoundVolume, Pitch, SoundStartTime);
			BlockTriggerBlock = true;
		}

		
	}


}
