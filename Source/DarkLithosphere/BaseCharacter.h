// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CoreCharacter.h"
//#include "SandboxCharacter.h"
#include "SandboxObjectMap.h"
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "BaseCharacter.generated.h"


class UBehaviorTree;
class ABaseCharacter;

UCLASS(BlueprintType, Blueprintable)
class DARKLITHOSPHERE_API UCharacterMap : public UDataAsset {
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "DW")
	TMap<int32, TSubclassOf<ACharacter>> CharacterTypeMap;
};


UCLASS()
class DARKLITHOSPHERE_API ABaseCharacter : public ACoreCharacter {
	GENERATED_BODY()

public:
	
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void OnDeath() override;

public:	

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	int SandboxTypeId = 0;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	int SandboxPlayerId = -1;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	bool bNoSerialization = false;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	UBehaviorTree* BehaviourTree;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	UStaticMeshComponent* CursorMesh;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	UAnimationAsset* DeathAnim;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	UAnimationAsset* TestAnim;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	UAnimMontage* MainAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	UAnimMontage* TwoHandMeeleAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	USoundCue* MeeleAttackSound;

	UPROPERTY(EditAnywhere, Category = "Sandbox")
	USoundCue* IdleSound;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PerformMainAttack();

	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Play Main Attack"))
	//void OnPlayMainAttack();

	UFUNCTION(BlueprintCallable, Category = "Sandbox")
	void OnFinishPlayMainAttack();

	UFUNCTION()
	void OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	UFUNCTION()
	void OnNotifyEndReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	virtual int GetTypeId();

	UContainerComponent* GetInventory(FString Name);

	void SelectActiveInventorySlot(int SlotId);

	//UFUNCTION()
	//void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	template<class T>
	T* GetFirstComponentByName(FString ComponentName) {
		TArray<T*> Components;
		GetComponents<T>(Components);
		for (T* Component : Components) {
			if (Component->GetName() == ComponentName)
				return Component;
		}

		return nullptr;
	}

	bool IsDead();

protected:

	bool bIsAttacking = false;

	bool bIsPlaySound = false;

	double LastIdleSound = 0;

protected:

	virtual bool CanMove();

	bool PlaySoundCue(USoundCue* SoundCue);

	UFUNCTION()
	void OnFinishSound();


private:

	//FOnMontageEnded MontageEndedDelegate;

	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	//double Timestamp;

	FVector GrassTraceLastPos;

	bool bIsEmptyHand = false;

};
