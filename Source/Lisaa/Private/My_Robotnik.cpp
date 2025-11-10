#include "My_Robotnik.h"

#include "GameFramework/CharacterMovementComponent.h"

AMy_Robotnik::AMy_Robotnik()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCharacterMovement() ->bOrientRotationToMovement = true;
	GetCharacterMovement() ->bUseControllerDesiredRotation = false;
	GetCharacterMovement() -> RotationRate = FRotator(0.0f, 720.f, 0.0f );

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationYaw = false;
}


void AMy_Robotnik::BeginPlay()
{
	Super::BeginPlay();
	
}




