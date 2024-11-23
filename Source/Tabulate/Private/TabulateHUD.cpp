//
// #include "TabulateTemplate.h"
// // #include "TabulateHUD.h"
//
//
// #include "EngineFontServices.h"
// #include "Debug/DebugDrawService.h"
// #include "Engine/Canvas.h"
// #include "Materials/MaterialParameterCollection.h"
// FDelegateHandle DebugDrawHandle;
// static bool GEableLLPOCDebugHUD = false;
//
//
//
// FString GetString();
//
// PRAGMA_DISABLE_OPTIMIZATION
//
// void OnDebugServiceDraw(UCanvas* Canvas, APlayerController* PC)
// {
//
// 	auto World = Canvas->GetWorld();
//
// 	UE_LOG(LogTemp, Log, TEXT("Begin"));
// 	
// 	for (TObjectIterator<UMaterialParameterCollection> It; It; ++It)
// 	{
// 		UMaterialParameterCollection* MaterialParameterCollection = *It;
// 		if (MaterialParameterCollection)
// 		{
// 			// 打印材质参数集合的名称
// 			UE_LOG(LogTemp, Log, TEXT("Found Material Parameter Collection: %s"), *MaterialParameterCollection->GetName());
// 		}
// 	}
//
// 	UE_LOG(LogTemp, Log, TEXT("End"));
//
// 	
// 	return;
// 	const UFont* Font = GEngine->GetAdditionalFont(3);
// 	// Canvas->GetCenter();
//
// 	auto a = GetString();
//
// 	FString s = FString::Printf(TEXT("++ ---------> ++ => -> ++ => -->"));
//
// 	UE_LOG(LogTemp, Warning, TEXT(" \n%s"), *a);
//
// 	TSharedPtr<FSlateFontCache> FontCache = FEngineFontServices::Get().GetFontCache();
// 	if( !FontCache.IsValid() )
// 	{
// 		return;
// 	}
//
// 	FSlateFontInfo FontInfo(Font, Font->LegacyFontSize);
//
//
// 	FShapedGlyphSequenceRef EntryNameShapedText = FontCache->ShapeBidirectionalText(s, FontInfo, 2, TextBiDi::ETextDirection::LeftToRight, ETextShapingMethod::FullShaping);
//
// 	FColor ForegroundColor = FColor::Yellow;
// 	
// 	FCanvasShapedTextItem ShapedTextItem(FVector2D(100, 100), EntryNameShapedText, FLinearColor(ForegroundColor));
// 	Canvas->DrawItem(ShapedTextItem);
//
// 	Canvas->DrawText(Font, *s, 200, 200, 2.f, 2.f);
//     
// }
//
// PRAGMA_ENABLE_OPTIMIZATION
//
// THIRD_PARTY_INCLUDES_START
//
// #include "Tabulate.h"
// THIRD_PARTY_INCLUDES_END
//
// FString GetString()
// {
// 	TArray<int32> Array = {
// 		FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(),
// 		FMath::Rand(), FMath::Rand(), FMath::Rand(), 121234078u
// 	};
//     
// 	// auto a = UTabulate::TArrayToTable(Array, 3, "Table 1: TempArray");
//
// 	
//
// 	using namespace tabulate;
// 	using Row_t = Table::Row_t;
//
//
// 	
// 	Table readme;
// 	readme.format().multi_byte_characters(true);
// 	readme.format().corner("·");
// 	readme.format().border_color(Color::yellow);
// 	readme.format()
// 						   .border_left("│")
// 							.border_right("│");
//
//     
// 	readme.add_row(Row_t{"tabn你好ihern C++吃什么\n 哈喽asdfasdfasdfasdf"});
// 	readme[0].format().font_align(FontAlign::center).font_color(Color::yellow);
//
// 	readme.add_row(Row_t{"httpsweish为什么"});
// 	readme[1]
// 		.format()
// 		.font_align(FontAlign::center)
// 		.font_style({FontStyle::underline, FontStyle::italic})
// 		.font_color(Color::white)
// 		.hide_border_top();
//
// 	// Table table;
// 	//
// 	// table.format().corner("♥")
// 	//   .font_style({FontStyle::bold})
// 	//   .corner_color(Color::magenta)
// 	//   .border_color(Color::magenta);
// 	//
// 	//
// 	// FString c(TEXT("我爱你哈哈哈哈哈哈哈哈"));
// 	// table.add_row({"Mandarin Chinese", TCHAR_TO_UTF8(*c)});
// 	//
// 	//
// 	// // Column 1 is using mult-byte characters
// 	// table.column(1).format()
// 	//   .multi_byte_characters(true);
// 	//
// 	// // Set English-US locale for first column
// 	// table.column(0).format().locale("en_US.UTF-8");
// 	// table[0][1].format().locale("en_US.UTF-8");
// 	//
// 	// // Set locale for individual cells
// 	// table[4][1].format().locale("zh_CN.UTF-8");  // Chinese
//
// 	Table table;
//
// 	table.format().corner("·")
// 	  .font_style({FontStyle::bold})
// 	  .corner_color(Color::magenta)
// 	  .border_color(Color::magenta);
//
// 	table.add_row({"English", "I love you"});
// 	table.add_row({"French", "Je t’aime"});
// 	table.add_row({"Spanish", "Te amo"});
// 	table.add_row({"German", "Ich liebe Dich"});
// 	table.add_row({"Mandarin Chinese", "Text Block -->我爱你-> --哈哈哈 \n 哈喽asdfasdfasdfasdf"});
// 	table.add_row({"Japanese", "愛してる"});
// 	table.add_row({"Korean", "사랑해 (Saranghae)"});
// 	table.add_row({"Greek", "Σ΄αγαπώ (Se agapo)"});
// 	table.add_row({"Italian", "Ti amo"});
// 	table.add_row({"Russian", "Я тебя люблю (Ya tebya liubliu)"});
//
// 	// Column 1 is using mult-byte characters
// 	table.column(1).format()
// 	  .multi_byte_characters(true);
// 	FString TableString(UTF8_TO_TCHAR(table.str().c_str()));
//
// 	return MoveTemp(TableString);
// 	// return a;
// }
//
// static void LLPOCToggleDebugHUD(const TArray<FString>& Args, UWorld* InWorld)
// {
// 	
// 	if(!DebugDrawHandle.IsValid())
// 	{
// 		DebugDrawHandle = UDebugDrawService::Register(TEXT("TextRender"), FDebugDrawDelegate::CreateStatic(&OnDebugServiceDraw));
// 	}
// 	else
// 	{
// 		UDebugDrawService::Unregister(DebugDrawHandle);
// 		DebugDrawHandle = FDelegateHandle();
// 	}
// }
//
// FAutoConsoleCommandWithWorldAndArgs LLPOCToggleDebugHUDCommand(
// 	TEXT("LLPOC.ToggleDebugHUD"),
// 	TEXT("ToggleDebugHUD Drawing"),
// 	FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(LLPOCToggleDebugHUD)
// 	);
