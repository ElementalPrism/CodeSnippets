// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BetterGameProject/Character/NatureCharacter.h"
#include "BetterGameProject/Character/TechCharacter.h"
#include "Sawblade.generated.h"

class ASawbladeTarget;


UCLASS()
class BETTERGAMEPROJECT_API ASawblade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASawblade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ASawbladeTarget* TargetA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ASawbladeTarget* TargetB;

	UPROPERTY(EditAnywhere)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY()
		ASawbladeTarget* NextPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeFrozen;

	float TimeFrozenCapture;


	bool ShouldMove;

	UPROPERTY(EditAnywhere, Category = "Damage")
		float SawbladeDamage = 10;

	FDamageEvent DamageEvent;
	//AController* NatureController;

	UFUNCTION()
		void OnComponentOverLapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentOverLapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
