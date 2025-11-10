#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class LISAA_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// ************** CAMERA + SPRING ARM **************

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	// ************** INPUT **************

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_Player;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MyMove;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MyLook;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_MyJump;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


	

private:
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 300.f;

};
