// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CUSTOM
	bAiming = false;

	// NOT AIMING CONTROL AND CONTROLLER MOVEMENT
	// Don't rotate when the Controller rotates. Let that just affect the camera 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Configure Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f); // at this rotation rate
	


	// Create a camera boom (pulls in towards the player if there is a collision)
	Cameraboom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	Cameraboom->SetupAttachment(RootComponent);
	Cameraboom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
	Cameraboom->bUsePawnControlRotation = true; // Rotate the arm based on the Controller
	
	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(Cameraboom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera DOES NOT rotate relative to arm


}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::MoveForward(float value)
{
	//FVector forward = GetActorForwardVector();
	//AddMovementInput(forward, value);

	// NOT AIMED MOVEMENT
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get Forward Vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AMainCharacter::MoveRight(float value)
{
	//FVector right = GetActorRightVector();
	//AddMovementInput(right, value);

	// NOT AIMED MOVEMENT
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get Forward Vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}



// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// CUSTOM FUNCTIONS

// Toggles zoom indictor
void AMainCharacter::toggleZoom()
{
	bAiming = !bAiming;
	if (bAiming == true)
	{
		Cameraboom->TargetArmLength = 100.0f;
	}
	else 
	{
		Cameraboom->TargetArmLength = 300.0f;
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// CUSTOM
	// Toggles zoom if player is pressing right mouse button
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AMainCharacter::toggleZoom);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AMainCharacter::toggleZoom);
}

