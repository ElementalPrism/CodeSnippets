// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleCogDoor.h"


// Sets default values
APuzzleCogDoor::APuzzleCogDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleCogDoor::BeginPlay()
{
	Super::BeginPlay();
	NumOfGears = GearBoxList.Num();
}

// Called every frame
void APuzzleCogDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckDoor();


}

void APuzzleCogDoor::CheckDoor()
{
	for (auto& Obj : GearBoxList) //automatically sets anything in the list as on object
	{
		
		if (Obj->GetIsSocketed() == true) 
		{
			Counter = Counter + 1; //if is socketed from each trigger is true add one to the counter
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, "Add 1 to counter");
			Obj->IsSocketed = false;

		}


	}


	if (Counter == NumOfGears) //if all of the gear triggers have cogs in them, open the door.
	{
		for (auto& Obj : CogDoorList)
		{
			if (!Obj)
			{
				return;
			}
			Obj->OpenDoor();
		}

	}



}

void APuzzleCogDoor::OpenDoor()
{
	
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, "Door Open");
		SetActorLocation(FMath::Lerp(this->GetActorLocation(), EndPoint, DoorSpeed)); //slides the door down


	/*if (GetActorLocation() == EndPoint)
	{
		return;
	}*/

}
