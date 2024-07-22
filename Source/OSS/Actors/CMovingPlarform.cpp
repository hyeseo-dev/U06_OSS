#include "CMovingPlarform.h"

ACMovingPlarform::ACMovingPlarform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	Speed = 100.f;
}

void ACMovingPlarform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	StartWS = GetActorLocation();
	TargetWS = GetTransform().TransformPosition(TargetLS);

}

void ACMovingPlarform::Tick(float DelaTime)
{
	Super::Tick(DelaTime);

	if (HasAuthority())
	{
		FVector CurrentLocation = GetActorLocation();

		float TotalDistance = (StartWS - TargetWS).Size();
		float CurrentDistance = (CurrentLocation - StartWS).Size();

		if (CurrentDistance >= TotalDistance)
		{
			FVector Temp = StartWS;
			StartWS = TargetWS;
			TargetWS = Temp;
		}

		FVector Direction = (TargetWS - StartWS).GetSafeNormal();

		CurrentLocation += Direction * Speed * DelaTime;
		SetActorLocation(CurrentLocation);
	}
}
