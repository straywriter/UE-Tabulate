
// #include "TabulateHUD.h"


#include "EngineFontServices.h"
#include "Debug/DebugDrawService.h"
#include "Engine/Canvas.h"
#include "Materials/MaterialParameterCollection.h"
FDelegateHandle DebugDrawHandle;
static bool GEableLLPOCDebugHUD = false;



FString GetLoveString();
FString GetArrayString();


PRAGMA_DISABLE_OPTIMIZATION

void OnDebugServiceDraw(UCanvas* Canvas, APlayerController* PC)
{
	// Nees set a font
	const UFont* Font = GEngine->GetAdditionalFont(1);
	if(Font)
	{
		// auto Show = GetLoveString();
		auto Show = GetArrayString();
		FString Ligature = FString::Printf(TEXT("Ligature : -> ++ =>"));

		TSharedPtr<FSlateFontCache> FontCache = FEngineFontServices::Get().GetFontCache();
		if( !FontCache.IsValid() )
		{
			return;
		}

		FSlateFontInfo FontInfo(Font, Font->LegacyFontSize);

		FShapedGlyphSequenceRef EntryNameShapedText = FontCache->ShapeBidirectionalText(Ligature, FontInfo, 1.5, TextBiDi::ETextDirection::LeftToRight, ETextShapingMethod::FullShaping);
		FColor ForegroundColor = FColor::Yellow;
	
		FCanvasShapedTextItem ShapedTextItem(FVector2D(100, 100), EntryNameShapedText, FLinearColor(ForegroundColor));
		// Canvas->DrawItem(ShapedTextItem);

		Canvas->DrawText(Font, *Show, 200, 200, 1.5f, 1.5f);
	}
}

PRAGMA_ENABLE_OPTIMIZATION

THIRD_PARTY_INCLUDES_START
#include <tabulate/table.hpp>
THIRD_PARTY_INCLUDES_END

#include "TabulateStatics.h"
#include "TabulateTemplate.h"


FString GetArrayString()
{
	TArray<int32> Array =
	{
		FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(),
		FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), 
	};
    
	return TabulateTemplate::TArrayToTable(Array, 1);
}

FString GetLoveString()
{
	using namespace tabulate;
	using Row_t = Table::Row_t;

	Table LoveTable;

	LoveTable.add_row({"English", "I love you"});
	LoveTable.add_row({"French", "Je t’aime"});
	LoveTable.add_row({"Spanish", "Te amo"});
	LoveTable.add_row({"German", "Ich liebe Dich"});
	LoveTable.add_row({"Mandarin Chinese", "我爱你"}).format().locale("zh_CN.UTF-8");
	LoveTable.add_row({"Greek", "Σ΄αγαπώ (Se agapo)"});
	LoveTable.add_row({"Italian", "Ti amo"});
	LoveTable.add_row({"Russian", "Я тебя люблю (Ya tebya liubliu)"});

	// Column 1 is using mult-byte characters
	LoveTable.column(1).format()
	  .multi_byte_characters(true);

	FTabulateStatics::ApplyTableFormat_Grid(LoveTable);

	FString TableString(UTF8_TO_TCHAR(LoveTable.str().c_str()));

	return MoveTemp(TableString);
}

static void LLPOCToggleDebugHUD(const TArray<FString>& Args, UWorld* InWorld)
{
	
	if(!DebugDrawHandle.IsValid())
	{
		DebugDrawHandle = UDebugDrawService::Register(TEXT("TextRender"), FDebugDrawDelegate::CreateStatic(&OnDebugServiceDraw));
	}
	else
	{
		UDebugDrawService::Unregister(DebugDrawHandle);
		DebugDrawHandle = FDelegateHandle();
	}
}

FAutoConsoleCommandWithWorldAndArgs LLPOCToggleDebugHUDCommand(
	TEXT("LLPOC.ToggleDebugHUD"),
	TEXT("ToggleDebugHUD Drawing"),
	FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(LLPOCToggleDebugHUD)
	);
