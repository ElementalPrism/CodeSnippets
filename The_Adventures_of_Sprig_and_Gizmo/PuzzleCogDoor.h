// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GearBoxTrigger.h"
#include "PuzzleCogDoor.generated.h"

UCLASS()
class BETTERGAMEPROJECT_API APuzzleCogDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleCogDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TArray<AGearBoxTrigger*> GearBoxList; //only gear box triggers can be put into this list

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DoorSpeed;

	UPROPERTY(EditAnywhere)
		FVector EndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<APuzzleCogDoor*> CogDoorList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ExtraDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> EndVectorList;


	UFUNCTION()
	void CheckDoor();


	UFUNCTION()
		void OpenDoor();



	int NumOfGears;
	int Counter = 0;

	bool DoorIsOpen;

};
