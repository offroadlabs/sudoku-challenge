#include <gtest/gtest.h>
#include "../src/core/sudoku.h"

class TestSudoku : public Sudoku
{
public:
    using Sudoku::findEmptyCell;
    using Sudoku::getIndex;
    using Sudoku::hasBlockConflict;
    using Sudoku::hasColumnConflict;
    using Sudoku::hasConflict;
    using Sudoku::hasRowConflict;
    using Sudoku::solve;
};

class SudokuTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Initialisation commune pour tous les tests
        emptyGrid = std::vector<Cell>(81);

        // Grille valide partiellement remplie
        validPartialGrid = std::vector<Cell>(81);
        // Remplir avec le motif de la capture d'écran (bloc par bloc, ligne par ligne)
        int validPattern[] = {
            0, 2, 7, 0, 0, 0, 0, 0, 9,
            0, 0, 4, 0, 0, 0, 0, 8, 7,
            0, 0, 9, 5, 7, 0, 2, 1, 0,

            2, 0, 0, 0, 1, 4, 0, 0, 0,
            1, 4, 8, 0, 9, 0, 0, 2, 6,
            3, 9, 5, 8, 2, 6, 7, 4, 1,

            0, 0, 0, 9, 0, 5, 0, 0, 0,
            8, 7, 0, 4, 0, 0, 9, 0, 1,
            0, 6, 0, 1, 3, 7, 0, 5, 0};
        for (int i = 0; i < 81; ++i)
        {
            validPartialGrid[i].setValue(validPattern[i]);
        }

        // Grille complète valide
        solvedGrid = std::vector<Cell>(81);
        int solvedPattern[] = {
            5, 3, 4, 6, 7, 8, 9, 1, 2,
            6, 7, 2, 1, 9, 5, 3, 4, 8,
            1, 9, 8, 3, 4, 2, 5, 6, 7,

            8, 5, 9, 7, 6, 1, 4, 2, 3,
            4, 2, 6, 8, 5, 3, 7, 9, 1,
            7, 1, 3, 9, 2, 4, 8, 5, 6,

            9, 6, 1, 5, 3, 7, 2, 8, 4,
            2, 8, 7, 4, 1, 9, 6, 3, 5,
            3, 4, 5, 2, 8, 6, 1, 7, 9};
        for (int i = 0; i < 81; ++i)
        {
            solvedGrid[i].setValue(solvedPattern[i]);
        }
    }

    std::vector<Cell> emptyGrid;
    std::vector<Cell> validPartialGrid;
    std::vector<Cell> solvedGrid;
};

// Test de la fonction getIndex
TEST_F(SudokuTest, GetIndexCalculatesCorrectly)
{
    EXPECT_EQ(TestSudoku::getIndex(0, 0), 0);
    EXPECT_EQ(TestSudoku::getIndex(0, 1), 1);
    EXPECT_EQ(TestSudoku::getIndex(1, 0), 3);
    EXPECT_EQ(TestSudoku::getIndex(8, 8), 80);
    EXPECT_EQ(TestSudoku::getIndex(4, 4), 40);
}

// Test de validation des mouvements
TEST_F(SudokuTest, ValidMovesAreRecognized)
{
    // Test sur une position vide dans la grille partielle
    EXPECT_TRUE(TestSudoku::isValidMove(validPartialGrid, 0, 0, 1));
    EXPECT_FALSE(TestSudoku::isValidMove(validPartialGrid, 0, 0, 4)); // 4 existe déjà dans la ligne
    EXPECT_FALSE(TestSudoku::isValidMove(validPartialGrid, 0, 0, 9)); // 9 existe déjà dans la colonne
}

// Test des conflits
TEST_F(SudokuTest, ConflictsAreDetectedCorrectly)
{
    // Test simple de conflit en ligne
    std::vector<Cell> testGrid(81);
    testGrid[TestSudoku::getIndex(0, 0)].setValue(5);
    EXPECT_TRUE(TestSudoku::hasRowConflict(testGrid, 0, 1, 5));  // Même valeur dans la ligne
    EXPECT_FALSE(TestSudoku::hasRowConflict(testGrid, 0, 1, 6)); // Valeur différente

    // Test simple de conflit en colonne
    testGrid = std::vector<Cell>(81);
    testGrid[TestSudoku::getIndex(0, 0)].setValue(5);
    EXPECT_TRUE(TestSudoku::hasColumnConflict(testGrid, 1, 0, 5));  // Même valeur dans la colonne
    EXPECT_FALSE(TestSudoku::hasColumnConflict(testGrid, 1, 0, 6)); // Valeur différente

    // Test simple de conflit en bloc
    testGrid = std::vector<Cell>(81);
    testGrid[TestSudoku::getIndex(0, 0)].setValue(5);
    EXPECT_TRUE(TestSudoku::hasBlockConflict(testGrid, 1, 1, 5));  // Même valeur dans le bloc
    EXPECT_FALSE(TestSudoku::hasBlockConflict(testGrid, 1, 1, 6)); // Valeur différente
}

// Test de recherche de cellule vide
TEST_F(SudokuTest, FindEmptyCellWorksCorrectly)
{
    auto [row, col] = TestSudoku::findEmptyCell(validPartialGrid);
    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 0);

    auto [rowSolved, colSolved] = TestSudoku::findEmptyCell(solvedGrid);
    EXPECT_EQ(rowSolved, -1);
    EXPECT_EQ(colSolved, -1);
}

// Test de résolution
TEST_F(SudokuTest, SolveWorksCorrectly)
{
    std::vector<Cell> gridToSolve = validPartialGrid;
    // on récupère la valeur du solve
    EXPECT_TRUE(TestSudoku::solve(gridToSolve));

    // Vérifier que la solution est valide en utilisant les fonctions existantes
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            // Vérifier que la cellule n'est pas vide
            int value = gridToSolve[TestSudoku::getIndex(row, col)].value();
            EXPECT_NE(value, 0) << "Cellule vide à la position (" << row << "," << col << ")";

            // Vérifier qu'il n'y a pas de conflit
            gridToSolve[TestSudoku::getIndex(row, col)].setValue(0); // Enlever temporairement la valeur
            EXPECT_TRUE(TestSudoku::isValidMove(gridToSolve, row, col, value))
                << "Conflit détecté à la position (" << row << "," << col << ") avec la valeur " << value;
            gridToSolve[TestSudoku::getIndex(row, col)].setValue(value); // Remettre la valeur
        }
    }
}

// Test de génération de grille
TEST_F(SudokuTest, GenerateGridProducesValidPuzzle)
{
    auto grid = TestSudoku::generateGrid(TestSudoku::Difficulty::EASY);

    // Vérifier que la grille est valide
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            if (!grid[TestSudoku::getIndex(row, col)].isEmpty())
            {
                EXPECT_FALSE(TestSudoku::hasConflict(grid, row, col,
                                                     grid[TestSudoku::getIndex(row, col)].value()));
            }
        }
    }

    // Vérifier que la grille est résolvable
    EXPECT_TRUE(TestSudoku::isSolvable(grid));
}

// Test des différents niveaux de difficulté
TEST_F(SudokuTest, DifficultyLevelsHaveCorrectEmptyCells)
{
    auto countEmptyCells = [](const std::vector<Cell> &grid)
    {
        return std::count_if(grid.begin(), grid.end(),
                             [](const Cell &cell)
                             { return cell.isEmpty(); });
    };

    auto easyGrid = TestSudoku::generateGrid(TestSudoku::Difficulty::EASY);
    EXPECT_EQ(countEmptyCells(easyGrid), 40);

    auto mediumGrid = TestSudoku::generateGrid(TestSudoku::Difficulty::MEDIUM);
    EXPECT_EQ(countEmptyCells(mediumGrid), 45);

    auto hardGrid = TestSudoku::generateGrid(TestSudoku::Difficulty::HARD);
    EXPECT_EQ(countEmptyCells(hardGrid), 50);

    auto expertGrid = TestSudoku::generateGrid(TestSudoku::Difficulty::EXPERT);
    EXPECT_EQ(countEmptyCells(expertGrid), 55);
}