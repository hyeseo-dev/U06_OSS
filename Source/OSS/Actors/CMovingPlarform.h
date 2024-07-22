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

private:
	UPROPERTY(EditAnywhere, Category = "MoveSpeed")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Target", meta = (MakeEditWidget))
	FVector TargetLS;

private:
	FVector StartWS;
	FVector TargetWS;
	
};
