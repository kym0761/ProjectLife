// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpeechBubbleBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpeechEnd);

class UTextBlock;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API USpeechBubbleBase : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* SpeechTextBlock;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* NameTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech")
		FString SpeechString;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Speech")
		int32 CurrentLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech")
		float SpeechSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech")
		float EndTime = 5.0f;

	virtual void NativeConstruct() override;

	FTimerHandle SpeechTimer;
	FTimerHandle SpeechEndTimer;
	UFUNCTION(BlueprintCallable, Category = "Speech")
		void StartSpeech(FString InSpeech);
	void Speech();
	
	FOnSpeechEnd OnSpeechEnd;
	void EndSpeech();

	void SetNameText(FString InName);

};
