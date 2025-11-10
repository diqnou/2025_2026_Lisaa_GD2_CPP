// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "My_Robotnik.generated.h"

UCLASS()
class LISAA_API AMy_Robotnik : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMy_Robotnik();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My_Robotnik")
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My_Robotnik")
	float TouchDamage = 10.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
