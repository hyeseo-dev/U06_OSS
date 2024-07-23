// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CMovingPlarform.generated.h"

UCLASS()
class OSS_API ACMovingPlarform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ACMovingPlarform();

protected:
	virtual void BeginPlay() override;

public:
	void Tick(float DelaTime) override;

public:
	void IncreaseActiveCount();
	void DecreaseActiveCount();

private:
	UPROPERTY(EditAnywhere, Category = "Moving")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Moving")
	int32 ActiveCount;

	UPROPERTY(EditAnywhere, Category = "Target", meta = (MakeEditWidget))
	FVector TargetLS;

private:
	FVector StartWS;
	FVector TargetWS;
	
};
