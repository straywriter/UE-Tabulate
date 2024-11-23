// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Tabulate.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TABULATE_API UTabulate : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Tabulate")
	static FString UClassUML(UClass* Class);

};
