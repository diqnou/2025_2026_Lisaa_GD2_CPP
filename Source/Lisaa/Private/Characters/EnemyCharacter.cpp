#include "Characters/EnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Slate/SGameLayerManager.h"
#include "Components/MyAttackEnemyComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0, 720.f, 0);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationYaw = false;

	AttackComp = CreateDefaultSubobject<UMyAttackEnemyComponent>(TEXT("AttackComp"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	
}

