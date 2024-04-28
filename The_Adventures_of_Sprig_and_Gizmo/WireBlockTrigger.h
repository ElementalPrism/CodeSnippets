// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"
#include "BetterGameProject/Interactables/WireLever.h"
#include "WireBlockTrigger.generated.h"

UENUM()
enum CheckForTheFollowingBox
{
	Red,
	Blue,
	Yellow
};






UCLASS()
class BETTERGAMEPROJECT_API AWireBlockTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWireBlockTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionArea;

	UFUNCTION()
		void OnComponentOverLapStart(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentOverLapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
		FVector BoxSize = { 50.f,50.f,50.f };

	UPROPERTY(EditAnywhere)
		FVector AreaClamp;

	//UPROPERTY(EditAnywhere)
	//	AWireLever* WireLever;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<CheckForTheFollowingBox> BoxCheck;

	UFUNCTION()
		bool GetIsSocketed();

	UPROPERTY(EditAnywhere)
		FQuat ResetRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ClampSpeed;

	UPROPERTY(EditAnywhere)
		FQuat NewRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* IncorrectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SoundStartTime;
	//UFUNCTION()
	//	void SpinCog(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool IsSocketed = false;
	bool IsRotation = false;

};
