#include <tabulate/table.hpp>
#include "Misc/AutomationTest.h"

using namespace tabulate;
using Row_t = Table::Row_t;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTabulateword_wrapping, "Tabulate.word_wrapping", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FTabulateword_wrapping::RunTest(const FString& Parameters){
  Table table;

  table.add_row(Row_t{"This paragraph contains a veryveryveryveryveryverylong "
                      "word. The long word will "
                      "break and word wrap to the next line.",
                      "This paragraph \nhas embedded '\\n' \ncharacters and\n "
                      "will break\n exactly "
                      "where\n you want it\n to\n break."});

  table[0][0].format().width(20);
  table[0][1].format().width(50);

  std::cout << table << std::endl;
  return true;
}
