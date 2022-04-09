// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CookWidget.generated.h"

class UItemSlot;
class UButton;
class ACookActor;
class UVerticalBox;
class UCookSelectionSlot;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UCookWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
		TArray<UItemSlot*> ItemSlotArray;

	UPROPERTY(Meta = (BindWidget))
	UItemSlot* ItemSlot_Result;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_DoCooking;

	UPROPERTY(Meta = (BindWidget))
		UVerticalBox* VerticalBox_CanDo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook")
		TSubclassOf<UCookSelectionSlot> CookSelectionSlotClass;

private:

	UPROPERTY()
		ACookActor* CookActorRef;

	UPROPERTY()
		FString CookResultName;

public:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void InitCookWidget();

	UFUNCTION()
	void UpdateCookWidget();

	//CookResultName의 값을 보내서 CookActor가 요리를 하도록 요청
	UFUNCTION()
		void Clicked_DoCooking();

	//CookActor의 인벤토리 내용물 바뀔때마다 제조 가능한 아이템 목록 업데이트
	void UpdateSelections();

	void SetCookResultName(FString InVal);

};
