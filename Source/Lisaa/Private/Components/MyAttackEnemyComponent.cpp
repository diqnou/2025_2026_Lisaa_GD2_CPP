#pragma once

#include "Components/MyAttackEnemyComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UMyAttackEnemyComponent::UMyAttackEnemyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMyAttackEnemyComponent::TryAttack(AActor* Target)
{
	if (!Target) return;
	if (!OwnerChar.IsValid()) 
		OwnerChar = Cast<ACharacter>(GetOwner());
	if (!OwnerChar.IsValid())
		return;

	UWorld* MyWorld = GetWorld();
	if (!MyWorld)
		return;
	const float Time = MyWorld->GetTimeSeconds();

	if (bAttacking || (Time	- LastAttackTime) < CoolDown)
		return;
	const float Dist2D = FVector::Dist2D(Target->GetActorLocation(), OwnerChar->GetActorLocation());
	if (Dist2D > Attackrange + HitRadius)
		return;
	const FVector Dir = (Target ->GetActorLocation() - OwnerChar->GetActorLocation());
	const FRotator TargetYaw = Dir.Rotation();
	OwnerChar->SetActorRotation(FMath::RInterpTo(OwnerChar->GetActorRotation(), TargetYaw, MyWorld->GetDeltaSeconds(), YawTurnrate));

	//if (FacingTolerancedeg > 0.f && IsFacingTarget(Target))
	//	return;

	bAttacking = true;
	Cachedtarget = Target;


	MyWorld->GetTimerManager().SetTimer(HitHandle, this, &UMyAttackEnemyComponent::DotHit, FMath::Max(0.f, WindUpTime), false);
	MyWorld->GetTimerManager().SetTimer(EndHandle, this, &UMyAttackEnemyComponent::EndAttack, FMath::Max(CoolDown, WindUpTime), false);
	
}

void UMyAttackEnemyComponent::DotHit()
{
	if (!OwnerChar.IsValid())
		return;

	AActor* Target = Cachedtarget.Get();
	if (!Target)
		return;


	const float Dist2D = FVector::Dist2D(Target->GetActorLocation(), OwnerChar->GetActorLocation());
	if (Dist2D > Attackrange + HitRadius)
		return;

	if (FacingTolerancedeg > 0.f && !IsFacingTarget(Target))
		return;


	if (UHealthComponent* HC = Target ->FindComponentByClass<UHealthComponent>())
	{

		HC ->ApplyDamageAt(Damage, OwnerChar.Get());
	}
}

void UMyAttackEnemyComponent::EndAttack()
{
	if (UWorld* MyWorld = GetWorld())
		LastAttackTime = MyWorld->GetTimeSeconds();

	bAttacking = false;
	Cachedtarget = nullptr;
}

bool UMyAttackEnemyComponent::IsFacingTarget(AActor* Target) const
{
	if (!OwnerChar.IsValid() || !Target	)
		return false;
	const FVector Forward = OwnerChar -> GetActorForwardVector().GetSafeNormal2D();
	const FVector Dir = (Target ->GetActorLocation() - OwnerChar->GetActorLocation());
	const float CosAngle = FVector::DotProduct(Forward, Dir);
	const float CosTresh = FMath :: Cos(FMath :: DegreesToRadians(FacingTolerancedeg));
	return CosAngle >= CosTresh;
	
}




