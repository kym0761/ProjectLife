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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cook")
		ACookActor* CookActorRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook")
		TSubclassOf<UCookSelectionSlot> CookSelectionSlotClass;

	UPROPERTY()
		FString CookResultName;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void InitCookWidget();

	UFUNCTION()
	void UpdateCookWidget();

	//CookResultName�� ���� ������ CookActor�� �丮�� �ϵ��� ��û
	UFUNCTION()
		void Clicked_DoCooking();

	//CookActor�� �κ��丮 ���빰 �ٲ𶧸��� ���� ������ ������ ��� ������Ʈ
	void UpdateSelections();
};
