#include "grid.h"
#include <algorithm>

Grid::Grid()
{
    clear();
}

int Grid::getValue(int row, int col) const
{
    return m_grid[row][col];
}

bool Grid::setValue(int row, int col, int value)
{
    if (value < 0 || value > 9)
        return false;
    if (row < 0 || row >= SIZE)
        return false;
    if (col < 0 || col >= SIZE)
        return false;

    if (value != 0 && !isValidInRow(row, value, col))
        return false;
    if (value != 0 && !isValidInColumn(col, value, row))
        return false;
    if (value != 0 && !isValidInBox(row, col, value, {row, col}))
        return false;

    m_grid[row][col] = value;
    return true;
}

bool Grid::isValid() const
{
    // Vérifier chaque ligne, colonne et boîte
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            int value = m_grid[i][j];
            if (value != 0)
            {
                // Vérifier si la valeur est valide en ignorant la position actuelle
                if (!isValidInRow(i, value, j) ||
                    !isValidInColumn(j, value, i) ||
                    !isValidInBox(i, j, value, {i, j}))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Grid::isSolved() const
{
    // Vérifier que la grille est valide et complète
    if (!isValid())
        return false;

    return std::all_of(m_grid.begin(), m_grid.end(),
                       [](const auto &row)
                       {
                           return std::all_of(row.begin(), row.end(),
                                              [](int value)
                                              { return value != 0; });
                       });
}

void Grid::clear()
{
    for (auto &row : m_grid)
    {
        row.fill(0);
    }
}

bool Grid::isValidInRow(int row, int value, int skipCol) const
{
    for (int col = 0; col < SIZE; ++col)
    {
        if (col != skipCol && m_grid[row][col] == value)
            return false;
    }
    return true;
}

bool Grid::isValidInColumn(int col, int value, int skipRow) const
{
    for (int row = 0; row < SIZE; ++row)
    {
        if (row != skipRow && m_grid[row][col] == value)
            return false;
    }
    return true;
}

bool Grid::isValidInBox(int row, int col, int value, std::pair<int, int> skip) const
{
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int currentRow = boxRow + i;
            int currentCol = boxCol + j;
            if ((currentRow != skip.first || currentCol != skip.second) &&
                m_grid[currentRow][currentCol] == value)
            {
                return false;
            }
        }
    }
    return true;
}