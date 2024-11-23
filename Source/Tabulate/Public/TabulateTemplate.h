#pragma once

#include "CoreMinimal.h"
#include "TabulateStatics.h"

THIRD_PARTY_INCLUDES_START
#include <tabulate/table.hpp>
THIRD_PARTY_INCLUDES_END

#include "Tabulate.h"

namespace TabulateTemplate
{
	template <typename ElementType>
	FString TArrayToTable(TArray<ElementType> Array, const uint32 ColumnNumber = 1, const FString ArrayName = FString())
	{
		// TODO: More type support
		static_assert(TIsArithmetic<ElementType>::Value);

		if (Array.IsEmpty() || ColumnNumber < 1)
			return FString();

		using namespace tabulate;
		using Row_t = Table::Row_t;

		// Table header
		const bool bHasHeader = !ArrayName.IsEmpty();
		Table TableName;
		if (bHasHeader)
		{
			TableName.format()
			         .font_align(FontAlign::center)
			         .multi_byte_characters(true);

			TableName.add_row(Row_t{reinterpret_cast<const char*>(StringCast<UTF8CHAR>(*ArrayName).Get())});
			TableName[0].format().font_align(FontAlign::center).hide_border();
		}

		Table ArrayTable;
		ArrayTable.format().multi_byte_characters(true);

		const uint32 RowNumber = static_cast<uint32>(std::ceil(static_cast<float>(Array.Num()) / ColumnNumber));

		Row_t HeaderText;
		for (auto Column = 0u; Column < ColumnNumber; ++Column)
		{
			HeaderText.push_back("Index");
			HeaderText.push_back("Value");
		}

		ArrayTable.add_row(HeaderText);

		ArrayTable[0][0].format().font_align(FontAlign::center);

		int32 ArrayIndex = 0;
		for (auto RawIndex = 0u; RawIndex < RowNumber; ++RawIndex)
		{
			Row_t Rows;
			for (auto ColumnIndex = 0u; ColumnIndex < ColumnNumber; ++ColumnIndex)
			{
				if (ArrayIndex < Array.Num())
				{
					const auto& Item = Array[ArrayIndex];
					Rows.push_back(std::string(StringCast<ANSICHAR>(*LexToString(ArrayIndex)).Get()));
					Rows.push_back(std::string(StringCast<ANSICHAR>(*LexToString(Item)).Get()));
					ArrayIndex++;
				}
				else
				{
					Rows.insert(Rows.end(), 2, " ");
				}
			}
			ArrayTable.add_row(Rows);
			for (auto ColumnIndex = 0u; ColumnIndex < ColumnNumber; ++ColumnIndex)
			{
				ArrayTable[RawIndex + 1][ColumnIndex * 2].format().font_align(FontAlign::center);
			}
		}

		FTabulateStatics::ApplyTableFormat_Grid(ArrayTable);

		// Table header
		if (bHasHeader)
		{
			TableName.add_row(Row_t{ArrayTable});
			TableName[1].format()
			            .hide_border()
			            .padding_top(0)
			            .border_left(" ")
			            .border_right(" ");
		}

		auto& Final = bHasHeader ? TableName : ArrayTable;

		FString TableString(UTF8_TO_TCHAR(Final.str().c_str()));

		return MoveTemp(TableString);
	}

}
