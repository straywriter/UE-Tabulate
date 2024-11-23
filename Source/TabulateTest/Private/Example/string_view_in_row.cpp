#include <tabulate/table.hpp>
#include "Misc/AutomationTest.h"

using namespace tabulate;
using Row_t = Table::Row_t;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTabulatestring_view_in_row, "Tabulate.string_view_in_row", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

#if __cplusplus >= 201703L
#include <string_view>
using std::string_view;
#else
#include <tabulate/string_view_lite.hpp>
using nonstd::string_view;
#endif

bool FTabulatestring_view_in_row::RunTest(const FString& Parameters){
  Table table;

  string_view c0 = "string_view";
  const char *c1 = "const char *";
  std::string c2 = "std::string";

  Table c3;
  c3.add_row({"Table", "", ""});
  c3.add_row({c0, c1, c2});
  c3[0].format().border("").corner("");

  table.add_row({c0, c1, c2, c3});

  std::cout << table << std::endl;
  return true;
}
