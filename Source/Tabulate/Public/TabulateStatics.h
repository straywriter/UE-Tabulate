#pragma once

#include "CoreMinimal.h"

THIRD_PARTY_INCLUDES_START
#include <tabulate/table.hpp>
THIRD_PARTY_INCLUDES_END


struct TABULATE_API FTabulateStatics
{
	static void ApplyTableFormat_Grid(tabulate::Table& Table);
	
};