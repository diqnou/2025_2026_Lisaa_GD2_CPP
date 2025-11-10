#include "Characters/MyCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (IMC_Player)
				{
					Subsystem->AddMappingContext(IMC_Player, 0);
				}
			}
		}
	}
	
}



void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	
}
