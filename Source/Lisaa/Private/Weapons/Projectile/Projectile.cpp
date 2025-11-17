#include "Weapons/Projectile/Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCol = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereCol->InitSphereRadius(8.0f);
	SphereCol->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCol->SetCollisionObjectType(ECC_WorldDynamic);
	SphereCol->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCol->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = SphereCol;
	SphereCol->SetSimulatePhysics(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->UpdatedComponent = SphereCol;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->bForceSubStepping = true;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

