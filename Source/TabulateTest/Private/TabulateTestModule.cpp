#include "TabulateTestModule.h"

DEFINE_LOG_CATEGORY(TabulateTest);

#define LOCTEXT_NAMESPACE "FTabulateTest"

void FTabulateTestModule::StartupModule()
{
	UE_LOG(TabulateTest, Warning, TEXT("TabulateTest module has been loaded"));
}

void FTabulateTestModule::ShutdownModule()
{
	UE_LOG(TabulateTest, Warning, TEXT("TabulateTest module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTabulateTestModule, TabulateTest)