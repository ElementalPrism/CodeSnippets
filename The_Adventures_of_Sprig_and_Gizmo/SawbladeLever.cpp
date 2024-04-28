// Fill out your copyright notice in the Description page of Project Settings.


#include "BetterGameProject/Puzzles/SawbladeLever.h"
#include "BetterGameProject/Puzzles/Sawblade.h"

// Sets default values
ASawbladeLever::ASawbladeLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
}
	

// Called when the game starts or when spawned
void ASawbladeLever::BeginPlay()
{
	Super::BeginPlay();
	TimeToButtonResetCapture = TimeToButtonReset;
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ASawbladeLever::OnComponentOverLapStart);
}


// Called every frame
void ASawbladeLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SteppedOn == true)
	{
		TimeToButtonReset = TimeToButtonReset - 1;

		if(TargetSawblade)
		{
			TargetSawblade->ShouldMove = false;
		}
		
	}

	if(TimeToButtonReset <= 0)
	{
		TimeToButtonReset = TimeToButtonResetCapture;
		SteppedOn = false;
	}
}

void ASawbladeLever::OnComponentOverLapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		SteppedOn = true;
	}
}
