// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MainCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());

	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	AttackSphere->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	FVector Location = GetActorLocation();

	EnemyController = Cast<AEnemyController>(GetController());

	EnemyController->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint1"), PatrolPoint1 + Location);
	EnemyController->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint2"), PatrolPoint2 + Location);

	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AgroSphereBeginOverlap);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::AgroSphereEndOverlap);
	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AttackSphereBeginOverlap);
	AttackSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::AttackSphereEndOverlap);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Setter for accelerating
void AEnemy::SetIsAccelerating(bool bAccelerating)
{
	bIsAccelerating = bAccelerating;
}

// Collision Functions
void AEnemy::AgroSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);

		if (Main)
		{
			if (EnemyController == nullptr)
			{
				EnemyController = Cast<AEnemyController>(GetController());
			}
			
			EnemyController->GetBlackboard()->SetValueAsObject(TEXT("TargetActor"), Main);
		}
	}
}

void AEnemy::AgroSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);

		if (Main)
		{
			if (EnemyController == nullptr)
			{
				EnemyController = Cast<AEnemyController>(GetController());
			}

			EnemyController->GetBlackboard()->SetValueAsObject(TEXT("TargetActor"), nullptr);
		}
	}
}

void AEnemy::AttackSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);

		if (Main)
		{
			if (EnemyController == nullptr)
			{
				EnemyController = Cast<AEnemyController>(GetController());
			}

			EnemyController->GetBlackboard()->SetValueAsBool(TEXT("InAttackRange"), true);
		}
	}
}

void AEnemy::AttackSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);

		if (Main)
		{
			if (EnemyController == nullptr)
			{
				EnemyController = Cast<AEnemyController>(GetController());
			}

			EnemyController->GetBlackboard()->SetValueAsBool(TEXT("InAttackRange"), false);
		}
	}
}