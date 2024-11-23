
#include "Misc/AutomationTest.h"
#include "TabulateTemplate.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TabulateArrayTest, "Tabulate.ArrayTest",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

using namespace TabulateTemplate;

bool TabulateArrayTest::RunTest(const FString& Parameters)
{
	const TArray<float> RandomFloatArray =
	{
		FMath::FRand(), FMath::FRand(), FMath::FRand(), FMath::FRand(), FMath::FRand(),
		FMath::FRand(), FMath::FRand(), FMath::FRand(), FMath::FRand(), FMath::FRand(),
	};

	UE_LOG(LogTemp, Warning, TEXT(" \n%s\n"), *TArrayToTable(RandomFloatArray));
	UE_LOG(LogTemp, Warning, TEXT(" \n%s\n"), *TArrayToTable(RandomFloatArray, 2));
	UE_LOG(LogTemp, Warning, TEXT(" \n%s\n"), *TArrayToTable(RandomFloatArray, 1, FString(TEXT("RandomFloatArray"))));
	
	return true;
}
