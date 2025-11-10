#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	UCameraComponent* Camera;

private:
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 300.f;

};
