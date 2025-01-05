#include "sudoku.h"
#include <QRandomGenerator>
#include <algorithm>

int Sudoku::getIndex(int row, int col)
{
    int blockRow = row / 3;
    int blockCol = col / 3;
    int blockIndex = blockRow * 3 + blockCol;

    int cellRow = row % 3;
    int cellCol = col % 3;
    int cellIndex = cellRow * 3 + cellCol;

    return blockIndex * 9 + cellIndex;
}

bool Sudoku::isValidMove(const std::vector<Cell> &grid, int row, int col, int number)
{
    return !hasConflict(grid, row, col, number);
}

bool Sudoku::hasConflict(const std::vector<Cell> &grid, int row, int col, int number)
{
    return hasRowConflict(grid, row, col, number) ||
           hasColumnConflict(grid, row, col, number) ||
           hasBlockConflict(grid, row, col, number);
}

bool Sudoku::hasRowConflict(const std::vector<Cell> &grid, int row, int col, int number)
{
    for (int c = 0; c < 9; c++)
    {
        if (c != col && grid[getIndex(row, c)].value() == number)
        {
            return true;
        }
    }
    return false;
}

bool Sudoku::hasColumnConflict(const std::vector<Cell> &grid, int row, int col, int number)
{
    for (int r = 0; r < 9; r++)
    {
        if (r != row && grid[getIndex(r, col)].value() == number)
        {
            return true;
        }
    }
    return false;
}

bool Sudoku::hasBlockConflict(const std::vector<Cell> &grid, int row, int col, int number)
{
    int blockRow = (row / 3) * 3;
    int blockCol = (col / 3) * 3;

    for (int r = blockRow; r < blockRow + 3; r++)
    {
        for (int c = blockCol; c < blockCol + 3; c++)
        {
            if ((r != row || c != col) && grid[getIndex(r, c)].value() == number)
            {
                return true;
            }
        }
    }
    return false;
}

std::pair<int, int> Sudoku::findEmptyCell(const std::vector<Cell> &grid)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (grid[getIndex(row, col)].isEmpty())
            {
                return {row, col};
            }
        }
    }
    return {-1, -1};
}

bool Sudoku::solve(std::vector<Cell> &grid)
{
    auto [row, col] = findEmptyCell(grid);
    if (row == -1)
        return true;

    for (int num = 1; num <= 9; num++)
    {
        if (!hasConflict(grid, row, col, num))
        {
            grid[getIndex(row, col)].setValue(num);

            if (solve(grid))
                return true;

            grid[getIndex(row, col)].setValue(0);
        }
    }
    return false;
}

std::vector<Cell> Sudoku::generateGrid(Difficulty difficulty)
{
    std::vector<Cell> grid(81);

    // Générer une grille complète
    fillBlock(grid, 0);
    fillBlock(grid, 4);
    fillBlock(grid, 8);

    if (!solve(grid))
    {
        return generateGrid(difficulty);
    }

    // Nombre de cases à vider selon la difficulté
    int cellsToRemove;
    switch (difficulty)
    {
    case Difficulty::EASY:
        cellsToRemove = 40;
        // cellsToRemove = 1; // Pour les tests
        break;
    case Difficulty::MEDIUM:
        cellsToRemove = 45;
        break;
    case Difficulty::HARD:
        cellsToRemove = 50;
        break;
    case Difficulty::EXPERT:
        cellsToRemove = 55;
        break;
    default:
        cellsToRemove = 40;
    }

    // Créer un vecteur d'indices et le mélanger
    std::vector<int> indices(81);
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), *QRandomGenerator::global());

    // Vider les cases sélectionnées
    for (int i = 0; i < cellsToRemove; ++i)
    {
        int index = indices[i];
        grid[index].setValue(0);
        grid[index].setInitial(false);
    }

    // Marquer les cases restantes comme initiales
    for (auto &cell : grid)
    {
        if (!cell.isEmpty())
        {
            cell.setInitial(true);
        }
    }

    return grid;
}

void Sudoku::fillBlock(std::vector<Cell> &grid, int blockIndex)
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::shuffle(numbers.begin(), numbers.end(), *QRandomGenerator::global());

    int startIndex = blockIndex * 9;
    for (int i = 0; i < 9; ++i)
    {
        grid[startIndex + i].setValue(numbers[i]);
        grid[startIndex + i].setInitial(true);
    }
}

bool Sudoku::isSolvable(std::vector<Cell> grid)
{
    return solve(grid);
}