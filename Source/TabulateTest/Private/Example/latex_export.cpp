#include <tabulate/latex_exporter.hpp>
#include "Misc/AutomationTest.h"

using namespace tabulate;
using Row_t = Table::Row_t;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTabulatelatex_export, "Tabulate.latex_export", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FTabulatelatex_export::RunTest(const FString& Parameters){
  Table movies;
  movies.add_row(Row_t{"S/N", "Movie Name", "Director", "Estimated Budget", "Release Date"});
  movies.add_row(Row_t{"tt1979376", "Toy Story 4", "Josh Cooley", "$200,000,000", "21 June 2019"});
  movies.add_row(Row_t{"tt3263904", "Sully", "Clint Eastwood", "$60,000,000", "9 September 2016"});
  movies.add_row(
      Row_t{"tt1535109", "Captain Phillips", "Paul Greengrass", "$55,000,000", " 11 October 2013"});

  // center align 'Director' column
  movies.column(2).format().font_align(FontAlign::center);

  // right align 'Estimated Budget' column
  movies.column(3).format().font_align(FontAlign::right);

  // right align 'Release Date' column
  movies.column(4).format().font_align(FontAlign::right);

  // Color header cells
  for (size_t i = 0; i < 5; ++i) {
    movies[0][i]
        .format()
        .font_color(Color::white)
        .font_style({FontStyle::bold})
        .background_color(Color::blue);
  }

  LatexExporter exporter;
  exporter.configure().indentation(8);
  auto latex = exporter.dump(movies);

  // tabulate::table
  std::cout << movies << "\n\n";

  // Exported Markdown
  std::cout << latex << std::endl;
  return true;
}
