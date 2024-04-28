// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Sawblade.h"
#include "SawbladeLever.generated.h"

//class ASawblade;

UCLASS()
class BETTERGAMEPROJECT_API ASawbladeLever : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASawbladeLever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ASawblade* TargetSawblade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeToButtonReset;
	float TimeToButtonResetCapture;

	bool SteppedOn;

	UFUNCTION()
		void OnComponentOverLapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
