// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			Main = Cast<AMainCharacter>(Pawn);
			Enemy = Cast<AEnemy>(Pawn);
		}
	}
}

void UMainAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = LateralSpeed.Size();
		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		// Setting yaw, pitch, and roll
		FRotator Rotation = Pawn->GetActorRotation();
		FRotator BaseAnimRotation = Pawn->GetBaseAimRotation();
		//FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(Rotation, BaseAnimRotation);
		FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(BaseAnimRotation, Rotation);
		UKismetMathLibrary::BreakRotator(Delta, Roll, Pitch, Yaw);


		if (Main == nullptr)
		{
			Main = Cast<AMainCharacter>(Pawn);
		}

		if (Main)
		{
			if (Main->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0)
			{
				bIsAccelerating = true;
			}
			else
			{
				bIsAccelerating = false;
			}
		}

		if (Enemy)
		{
			bIsAccelerating = Enemy->bIsAccelerating;
		}
		else
		{
			Enemy = Cast<AEnemy>(Pawn);
			if (Enemy)
			{
				bIsAccelerating = Enemy->bIsAccelerating;
			}
		}
	}
}

