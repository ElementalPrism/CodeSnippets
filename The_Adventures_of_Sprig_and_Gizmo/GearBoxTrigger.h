// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GearBoxTrigger.generated.h"

UCLASS()
class BETTERGAMEPROJECT_API AGearBoxTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGearBoxTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionArea;
	
	UFUNCTION()
	void OnComponentOverLapStart(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                             class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentOverLapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                           class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                           const FHitResult& SweepResult);

	UPROPERTY()
	FVector BoxSize = {50.f, 50.f, 50.f};

	UPROPERTY(EditAnywhere)
	FVector AreaClamp;

	UFUNCTION()
	bool GetIsSocketed();

	UPROPERTY(EditAnywhere)
	FQuat ResetRotation;

	UPROPERTY(EditAnywhere)
	FQuat NewRotation;

	UPROPERTY(EditAnywhere)
	float ClampSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LogOnly;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPrimitiveComponent* LogPrimitiveComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LerpTime;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* PassageAvailable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SoundPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SoundStartTime;

	//UFUNCTION()
	//	void SpinCog(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	USceneComponent* CogPass;


	bool IsSocketed = false;
	bool IsRotation = false;
	bool ClampStop = false;
	bool StartLerp = false;
	bool DoneLerping = false;
};
