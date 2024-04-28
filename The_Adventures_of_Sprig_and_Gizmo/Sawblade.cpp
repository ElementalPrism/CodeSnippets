// Fill out your copyright notice in the Description page of Project Settings.


#include "BetterGameProject/Puzzles/Sawblade.h"

#include "SawbladeTarget.h"

// Sets default values
ASawblade::ASawblade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASawblade::BeginPlay()
{
	Super::BeginPlay();
	NextPoint = TargetA;
	ShouldMove = true;
	TimeFrozenCapture = TimeFrozen;
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ASawblade::OnComponentOverLapStart);
	HitBox->OnComponentEndOverlap.AddDynamic(this, &ASawblade::OnComponentOverLapEnd);
}

// Called every frame
void ASawblade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetA || !TargetB)
	{
		GLog->Log("Missing Target");
		return;
	}

	if(ShouldMove == true)
	{
		SetActorLocation(FMath::VInterpConstantTo(this->GetActorLocation(), NextPoint->GetActorLocation(), DeltaTime, MovementSpeed));
	}

	if (ShouldMove == false)
	{
		TimeFrozen = TimeFrozen - DeltaTime;

		if (TimeFrozen <= 0)
		{
			TimeFrozen = TimeFrozenCapture;
			ShouldMove = true;
		}

	}




	if (FVector::Distance(GetActorLocation(), TargetA->GetActorLocation()) < 5.0f)
	{
		NextPoint = TargetB;
	}

	if (FVector::Distance(GetActorLocation(), TargetB->GetActorLocation()) < 5.0f)
	{
		NextPoint = TargetA;
	}


}

void ASawblade::OnComponentOverLapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GLog->Log("Sawblade Hit");

	if (OtherActor->ActorHasTag("Character"))
	{
		OtherActor->TakeDamage(SawbladeDamage, DamageEvent, nullptr, this);
	}
}

void ASawblade::OnComponentOverLapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GLog->Log("Sawblade End");
}
