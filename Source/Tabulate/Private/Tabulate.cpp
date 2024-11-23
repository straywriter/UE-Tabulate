#include "Tabulate.h"

#include "UObject/UnrealTypePrivate.h"
#include "TabulateStatics.h"

THIRD_PARTY_INCLUDES_START
#include <tabulate/table.hpp>
#include <tabulate/markdown_exporter.hpp>
THIRD_PARTY_INCLUDES_END


FString UTabulate::UClassUML(UClass* Class)
{
    for (TFieldIterator<FProperty> PropIt(Class); PropIt; ++PropIt)
    {
        FProperty* Property = *PropIt;
        FString PropertyType = Property->GetCPPType();
        UE_LOG(LogTemp, Warning, TEXT("Property: %s, Type: %s"), *Property->GetName(), *PropertyType);
    }

    for (TFieldIterator<UBoolProperty> PropIt(Class); PropIt; ++PropIt)
    {
        UProperty* Property = *PropIt;
        UE_LOG(LogTemp, Warning, TEXT("Property: %s"), *Property->GetName());
    }

    // 打印所有方法
    for (TFieldIterator<UFunction> FuncIt(Class, EFieldIteratorFlags::IncludeSuper); FuncIt; ++FuncIt)
    {
        UFunction* Function = *FuncIt;
        // UE_LOG(LogTemp, Warning, TEXT("Function: %s"), *Function->SingletonPtr());
    }
    
    for (TFieldIterator<UFunction> FuncIt(Class); FuncIt; ++FuncIt)
    {
        UFunction* Function = *FuncIt;
        FString FunctionName = Function->GetName();
        FString FunctionParams;

        for (TFieldIterator<FProperty> PropIt(Function); PropIt; ++PropIt)
        {
            FProperty* Property = *PropIt;
            FunctionParams += Property->GetCPPType();
            FunctionParams += TEXT(" ");
            FunctionParams += Property->GetName();
            FunctionParams += TEXT(", ");
        }

        // Remove the last comma and space
        if (FunctionParams.Len() >= 2)
        {
            FunctionParams = FunctionParams.LeftChop(2);
        }

        FProperty* ReturnProp = Function->GetReturnProperty();
        FString ReturnType = ReturnProp ? ReturnProp->GetCPPType() : TEXT("void");;

        FString FunctionSignature = ReturnType + TEXT(" ") + FunctionName + TEXT("(") + FunctionParams + TEXT(")");
        UE_LOG(LogTemp, Warning, TEXT("Function: %s"), *FunctionSignature);
    }

    using namespace tabulate;
    using Row_t = Table::Row_t;

    Table ClassTable;
    
    // reinterpret_cast<const char*>(StringCast<UTF8CHAR>(*Row).Get())
    
    ClassTable.add_row(Row_t{reinterpret_cast<const char*>(StringCast<UTF8CHAR>(*Class->GetFullName()).Get())});
    ClassTable.format().multi_byte_characters(true).font_align(FontAlign::center);

    Table PropertyTable;

    for (TFieldIterator<FProperty> PropIt(Class); PropIt; ++PropIt)
    {
        const FProperty* Property = *PropIt;
        FString PropertyType = Property->GetCPPType();
        auto Row = FString::Format(TEXT("{0}:{1}"), {*Property->GetName(), *PropertyType});
        PropertyTable.add_row(Row_t{reinterpret_cast<const char*>(StringCast<UTF8CHAR>(*Row).Get())});
    }
    // ClassTable.format().corner("--- --. .")
    FTabulateStatics::ApplyTableFormat_Grid(PropertyTable);


    ClassTable.add_row({PropertyTable});

    Table FunctionTable;
    
    FTabulateStatics::ApplyTableFormat_Grid(ClassTable);

    FString TableString(UTF8_TO_TCHAR(ClassTable.str().c_str()));
    // FString TableString(UTF8_TO_TCHAR(PropertyTable.str().c_str()));

    UE_LOG(LogTemp, Warning, TEXT(" \n%s"), *TableString);
    
    FString a;
    return a;
    
}



// FDelegateHandle DebugDrawHandle;
// static bool GEableLLPOCDebugHUD = false;



// void OnDebugServiceDraw(UCanvas* Canvas, APlayerController* PC)
// {
//     TArray<int32> Array = {
//         FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(),
//         FMath::Rand(), FMath::Rand(), FMath::Rand(), 121234078u
//     };
//     
//     auto a = UTabulate::TArrayToTable(Array, 3, "Table 1: TempArray");
//     const UFont* Font = GEngine->GetSmallFont();
//     // Canvas->GetCenter();
//
//     Canvas->DrawText(Font, *a, 100, 100);
//     
// }
//
//
// static void LLPOCToggleDebugHUD(const TArray<FString>& Args, UWorld* InWorld)
// {
// 	
//     if(!DebugDrawHandle.IsValid() && GEableLLPOCDebugHUD)
//     {
//         DebugDrawHandle = UDebugDrawService::Register(TEXT("TextRender"), FDebugDrawDelegate::CreateStatic(&OnDebugServiceDraw));
//     }
//     else
//     {
//         UDebugDrawService::Unregister(DebugDrawHandle);
//         DebugDrawHandle = FDelegateHandle();
//     }
// }
//
// FAutoConsoleCommandWithWorldAndArgs LLPOCToggleDebugHUDCommand(
//     TEXT("LLPOC.ToggleDebugHUD"),
//     TEXT("ToggleDebugHUD Drawing"),
//     FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(LLPOCToggleDebugHUD)
//     );








// static void  SetGridFormat(tabulate::Table& Table)
// {
//     Table.format().multi_byte_characters(true);
//
//     // Set border
//     Table.format()
//          .border_top("─")
//          .border_bottom("─")
//          .border_left("│")
//          .border_right("│");
//
//     // Set corner
//     for (auto RowIndex = 0; RowIndex < Table.get_rows(); RowIndex++)
//     {
//         for (auto ColumnIndex = 0; ColumnIndex < Table.get_cols(); ColumnIndex++)
//         {
//             auto TableCornerCharset = GetCornerChar_GridFormat(RowIndex,
//                                                                ColumnIndex,
//                                                                Table.get_rows(),
//                                                                Table.get_cols());
//
//             Table.format()
//                  .corner_top_left(TableCornerCharset.CornerTopLeft)
//                  .corner_top_right(TableCornerCharset.CornerTopRight)
//                  .corner_bottom_left(TableCornerCharset.CornerBottomLeft)
//                  .corner_bottom_right(TableCornerCharset.CornerBottomRight);
//         }
//     }
// }

// static FString SetTableFormat(tabulate::Table Table, UTabulate::ETableFormat TableFormat)
// {
//     FString TableString;
//
//     switch (TableFormat)
//     {
//     case UTabulate::ETableFormat::Markdown:
//         {
//             
//             break;
//         }
//         // TableString = markdown_exporter(table);
//     case UTabulate::ETableFormat::Grid:
//         {
//             SetGridFormat(Table);
//             break;
//         }
//         // TableString = table_to_string(table, TableFormat::grid);
//     case UTabulate::ETableFormat::SimpleOutline:
//         // TableString = table_to_string(table, TableFormat::simple_outline);
//         break;
//     case UTabulate::ETableFormat::FancyOutline:
//         // TableString = table_to_string(table, TableFormat::fancy_outline);
//         break;
//     default:
//         // UTabulate::ETableFormat::Default
//         break;
//     }
//     
//
//     return TableString;
// }

// void UTabulate::Test123()
// {
//
//
//     using namespace tabulate;
//     using Row_t = Table::Row_t;
//
//
//
//         Table readme;
//     readme.format().multi_byte_characters(true);
//     readme.format().corner("·");
// readme.format().border_color(Color::yellow);
//     readme.format()
//                            .border_left("│")
//                             .border_right("│");
//
//     
// readme.add_row(Row_t{"tabulate for Modern C++"});
// readme[0].format().font_align(FontAlign::center).font_color(Color::yellow);
//
// readme.add_row(Row_t{"https://github.com/p-ranav/tabulate"});
// readme[1]
//     .format()
//     .font_align(FontAlign::center)
//     .font_style({FontStyle::underline, FontStyle::italic})
//     .font_color(Color::white)
//     .hide_border_top();
//
// readme.add_row(Row_t{"Tabulate is a header-only library for printing aligned, formatted, and "
//                      "colorized tables in Modern C++"});
//     FString TableString(UTF8_TO_TCHAR(readme.str().c_str()));
//
//
//     UE_LOG(LogTemp, Warning, TEXT(" \n%s"), *TableString);
//
//     DumpUClassUML(AActor::StaticClass());
//
//
//     
//     TArray<int32> Array = {
//         FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(), FMath::Rand(),
//         FMath::Rand(), FMath::Rand(), FMath::Rand(), 121234078u
//     };
//  
// 	auto a = TArrayToTable(Array, 3, "Table 1: TempArray");
//  //
//  UE_LOG(LogTemp, Warning, TEXT(" \n%s"), *a);
//  //
//  //
//  //    TArray<float> Array1 = {
//  //        FMath::FRand(), FMath::FRand(), FMath::FRand(), FMath::FRand(), FMath::FRand(), FMath::FRand(), FMath::FRand(),
//  //        FMath::FRand(), FMath::FRand(), FMath::FRand(), 1234123094.12312f
//  //    };
//  //
//  //
//  //    auto c = TArrayToTable(Array1);
//  //
//  //    UE_LOG(LogTemp, Warning, TEXT(" \n%s"), *c);
//
// }
