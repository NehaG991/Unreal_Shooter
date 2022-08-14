// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy.generated.h"


UCLASS()
class UNREAL_SHOOTER_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere, Category = "Pawn")
		class UBehaviorTree* BehaviorTree;

	//UPROPERTY(EditAnywhere, Category = "BehaviorTree", Meta = (MakeEditWidget = true))
	//	FVector PatrolPoint1;

	//UPROPERTY(EditAnywhere, Category = "BehaviorTree", Meta = (MakeEditWidget = true))
	//	FVector PatrolPoint2;

	UPROPERTY(BlueprintReadWrite, Category = "BehaviorTree")
	class AEnemyController* EnemyController;

	UPROPERTY(BlueprintReadOnly)
		bool bIsAccelerating;

	UFUNCTION(BlueprintCallable)
		void SetIsAccelerating(bool bAccelerating);

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
		class USphereComponent* AgroSphere;

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
		class USphereComponent* AttackSphere;

	//UFUNCTION(BlueprintCallable)
	//	void AgroSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//UFUNCTION(BlueprintCallable)
	//	void AgroSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//UFUNCTION(BlueprintCallable)
	//	void AttackSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//UFUNCTION(BlueprintCallable)
	//	void AttackSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
