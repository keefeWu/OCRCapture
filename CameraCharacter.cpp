// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraCharacter.h"
#include "global.h"
#include <ctime>
#include "ImageUtils.h"
#include "string"
// Sets default values
ACameraCharacter::ACameraCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetupAttachment(RootComponent);
	SceneCapture->bCaptureEveryFrame = false;
	SceneCapture->bCaptureOnMovement = false;
	SceneCapture->LODDistanceFactor = 3; //Force bigger LODs for faster computations
	SceneCapture->bEnableClipPlane = true;
	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	textureTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("texureTarget"));
	textureTarget->ResizeTarget(1024, 1024);
	SceneCapture->TextureTarget = textureTarget;

	srand((int)time(0));
	pic_idx_ = 0;
}

// Called when the game starts or when spawned
void ACameraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
bool SaveRenderTargetToFile(UTextureRenderTarget2D* rt, const FString& fileDestination)
{
	UE_LOG(LogTemp, Warning, TEXT("SaveRenderTargetToFile"));

	if (rt == nullptr)
	{
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("rt"));

	FTextureRenderTargetResource* rtResource = rt->GameThread_GetRenderTargetResource();
	FReadSurfaceDataFlags readPixelFlags(RCM_UNorm);

	TArray<FColor> outBMP;
	outBMP.AddUninitialized(rt->GetSurfaceWidth() * rt->GetSurfaceHeight());
	rtResource->ReadPixels(outBMP, readPixelFlags);

	for (FColor& color : outBMP)
		color.A = 255;

	FIntPoint destSize(rt->GetSurfaceWidth(), rt->GetSurfaceHeight());
	TArray<uint8> CompressedBitmap;
	FImageUtils::CompressImageArray(destSize.X, destSize.Y, outBMP, CompressedBitmap);
	bool imageSavedOk = FFileHelper::SaveArrayToFile(CompressedBitmap, *fileDestination);
	//bool imageSavedOk = true;
	return imageSavedOk;
}
void ACameraCharacter::Capture(bool isMask)
{
	std::string path = "F:\\data\\text\\";
	path += std::to_string(pic_idx_);
	if (isMask)
	{
		path += "_mask.png";
		pic_idx_++;
	}
	else{
		float location[3];
		float rotation[3];
		for (int i = 0; i < 3; i++)
		{
			location[i] = rand() % 100;
			rotation[i] = rand() % 10;
		}
		SetActorLocationAndRotation(FVector(-50.f + location[0], 200.f + location[1], 450.f + location[2]),
			FRotator(265.f + rotation[0], -5.f + rotation[0], -5.f + rotation[0]), false, 0, ETeleportType::None);
		path += ".png";
	}
	SceneCapture->CaptureScene();
	SaveRenderTargetToFile(textureTarget, path.c_str());
}
// Called every frame
void ACameraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (g_status_code)
	{
	case 2:
		Capture(false);
		g_status_code++;
		break;
	case 5:
		Capture(true);
		g_status_code = 0;
	}
}

// Called to bind functionality to input
void ACameraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

