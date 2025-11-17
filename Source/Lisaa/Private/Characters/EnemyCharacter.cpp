#include "Characters/EnemyCharacter.h"

#include "Components/EnemyAttackComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Slate/SGameLayerManager.h"

AEnemyCharacter::AEnemyCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0, 720.f, 0);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationYaw = false;

	AttackComp = CreateDefaultSubobject<UEnemyAttackComponent>(TEXT("AttackComp"));
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	if (HealthComp)
	{
		HealthComp->OnDeath.AddDynamic(this, &AEnemyCharacter::OnSelfDeath);
	}
	
}

void AEnemyCharacter::OnSelfDeath(AActor* DeadActor)
{
	// PLAY VFX ; SFX
	Destroy();
}

