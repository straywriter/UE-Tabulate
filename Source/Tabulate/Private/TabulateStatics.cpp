#include "TabulateStatics.h"


struct CornerCharset
{
    std::string CornerTopLeft;
    std::string CornerTopRight;
    std::string CornerBottomLeft;
    std::string CornerBottomRight;
};

CornerCharset GetCornerChar_GridFormat(uint32 Row, uint32 Column, uint32 RowCount, uint32 ColumnCount)
{
    CornerCharset TableCornerCharset;

    if (Row == 0)
    {
        if (Column == 0)
            TableCornerCharset = {"┌", "┐", "└", "┘"};
        else if (Column == ColumnCount - 1)
            TableCornerCharset = {"┬", "┐", "└", "┘"};
        else
            TableCornerCharset = {"┬", "┬", "┴", "┴"};
    }
    else if (Row == RowCount - 1)
    {
        if (Column == 0)
            TableCornerCharset = {"├", "┤", "└", "┘"};
        else if (Column == ColumnCount - 1)
            TableCornerCharset = {"┼", "┤", "┴", "┘"};
        else
            TableCornerCharset = {"┼", "┼", "┴", "┴"};
    }
    else
    {
        if (Column == 0)
            TableCornerCharset = {"├", "┤", "├", "┼"};
        else if (Column == ColumnCount - 1)
            TableCornerCharset = {"┼", "┤", "┼", "┤"};
        else
            TableCornerCharset = {"┼", "┼", "┼", "┼"};
    }

    return TableCornerCharset;
}

void FTabulateStatics::ApplyTableFormat_Grid(tabulate::Table& Table)
{
    for (auto RowIndex = 0; RowIndex < Table.get_rows(); RowIndex++)
    {
        for (auto ColumnIndex = 0; ColumnIndex < Table.get_cols(); ColumnIndex++)
        {
            // Set corner
            auto TableCornerCharset = GetCornerChar_GridFormat(RowIndex,
                                                               ColumnIndex,
                                                               Table.get_rows(),
                                                               Table.get_cols());
            Table[RowIndex][ColumnIndex].format()
                            .corner_top_left(TableCornerCharset.CornerTopLeft)
                            .corner_top_right(TableCornerCharset.CornerTopRight)
                            .corner_bottom_left(TableCornerCharset.CornerBottomLeft)
                            .corner_bottom_right(TableCornerCharset.CornerBottomRight);

            // Set border
            Table[RowIndex][ColumnIndex].format()
                                        .border_top("─").border_bottom("─").border_left("│")
                                        .border_right("│");
        }
    }
}