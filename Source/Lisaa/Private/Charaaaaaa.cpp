// Fill out your copyright notice in the Description page of Project Settings.


#include "Charaaaaaa.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharaaaaaa::ACharaaaaaa()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 450.f;
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Caméra"));
    Camera->SetupAttachment(SpringArm);
    Camera->bUsePawnControlRotation = false;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;



}
void ACharaaaaaa::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LP = PC-> GetLocalPlayer())
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

void ACharaaaaaa::Move(const FInputActionValue& Value)
{
 const FVector2D Axis = Value.Get<FVector2D>();

    if (Controller && (Axis.Size() > 0.f))
    {
        const FRotator Yawrot(0.f, Controller -> GetControlRotation().Yaw, 0.0f);
        const FVector Forward = FRotationMatrix(Yawrot).GetUnitAxis(EAxis :: X);
        const FVector Right = FRotationMatrix(Yawrot).GetUnitAxis(EAxis::Y);

        AddMovementInput(Right, Axis.X);
        AddMovementInput(Forward, Axis.Y);
    }
}

void ACharaaaaaa::Look(const FInputActionValue& Value)
{
 const FVector2D Axis = Value.Get<FVector2D>();
    AddControllerPitchInput(Axis.Y);
    AddControllerYawInput(Axis.X);
    
}

// Called every frame
void ACharaaaaaa::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharaaaaaa::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* ETC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (IA_MyMove)
        {
            ETC->BindAction(IA_MyMove, ETriggerEvent::Triggered, this, &ACharaaaaaa::Move);
        }
        if (IA_MyLook)
        {
            ETC->BindAction(IA_MyLook, ETriggerEvent::Triggered, this, &ACharaaaaaa::Look);
        }
        if (IA_MyJump)
        {
            ETC->BindAction(IA_MyJump, ETriggerEvent::Started, this, &ACharaaaaaa::Move);
        }

    }
}
