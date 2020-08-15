// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "CameraCharacter.generated.h"

UCLASS()
class OCRCAPTURE_API ACameraCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACameraCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USpringArmComponent* OurCameraSpringArm;
	UCameraComponent* OurCamera;
	UPROPERTY(EditAnywhere, Category = "Components")
		USceneCaptureComponent2D* SceneCapture;
	UPROPERTY(EditAnywhere, Category = "Components")
		class UTextureRenderTarget2D* textureTarget;

	void Capture(bool isMask);
	int pic_idx_;
};
