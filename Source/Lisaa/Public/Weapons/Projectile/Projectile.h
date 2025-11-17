#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class LISAA_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	UFUNCTION(BlueprintCallable)
	void InitShot(AActor* InOwner, float Speed);

	UFUNCTION(BlueprintCallable)
	void SetDamage(float InDamage) { Damage = InDamage; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCol = nullptr;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float LifeSeconds = 3.f;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* Comp, AActor* Other,UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	
private:
	float Damage = 10.f;


};
