#include <tabulate/table.hpp>
#include "Misc/AutomationTest.h"

using namespace tabulate;
using Row_t = Table::Row_t;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTabulateshape, "Tabulate.shape", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

void print_shape(Table &table) {
  auto shape = table.shape();
  std::cout << "Shape: (" << shape.first << ", " << shape.second << ")" << std::endl;
}

bool FTabulateshape::RunTest(const FString& Parameters){
  Table table;
  table.add_row(Row_t{"Command", "Description"});
  table.add_row(Row_t{"git status", "List all new or modified files"});
  table.add_row(Row_t{"git diff", "Show file differences that haven't been staged"});
  std::cout << table << std::endl;
  print_shape(table);
  return true;
}
