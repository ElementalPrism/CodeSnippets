// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BetterGameProject/Grabbables/GrabbableActor.h"
#include "WireBlockTrigger.h"
#include "GrabbableWire.generated.h"

/**
 * 
 */
UCLASS()
class BETTERGAMEPROJECT_API AGrabbableWire : public AGrabbableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrabbableWire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsMoving;
	bool BlockTriggerBlock = false;
	FVector Clamp;
	float NewClampSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AWireBlockTrigger* BlockTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* InsertSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SoundStartTime;

};
