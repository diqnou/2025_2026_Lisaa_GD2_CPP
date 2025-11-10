// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Charaaaaaa.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class LISAA_API ACharaaaaaa : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharaaaaaa();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_Player;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MyMove;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MyLook;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MyJump;

	void Move(const FInputActionValue & Value);
	void Look(const FInputActionValue & Value);



private : 
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 300.f;
	float MoveSpeed = 300.f;


};
