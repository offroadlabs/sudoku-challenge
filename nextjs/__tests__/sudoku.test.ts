import { describe, expect, test } from "bun:test";
import { generateSudoku, isSolvable, isValidMove } from "@/lib/sudoku-generator";
import { CELLS_TO_REMOVE } from "@/types/difficulty";
import { isLineComplete, isColumnComplete, isBlockComplete } from "@/lib/score-calculator";

describe("Fonctions utilitaires du Sudoku", () => {
  test("isValidMove vérifie correctement les mouvements valides", () => {
    const grid = Array(9).fill(null).map(() => Array(9).fill(0));
    grid[0][0] = 5;

    // Test de conflit en ligne
    expect(isValidMove(grid, 0, 1, 5)).toBe(false);
    expect(isValidMove(grid, 0, 1, 6)).toBe(true);

    // Test de conflit en colonne
    expect(isValidMove(grid, 1, 0, 5)).toBe(false);
    expect(isValidMove(grid, 1, 0, 6)).toBe(true);

    // Test de conflit en bloc
    expect(isValidMove(grid, 1, 1, 5)).toBe(false);
    expect(isValidMove(grid, 1, 1, 6)).toBe(true);
  });

  test("isSolvable détecte correctement les grilles résolvables", () => {
    console.log("Début du test isSolvable");
    // Grille vide (résolvable)
    const emptyGrid = Array(9).fill(null).map(() => Array(9).fill(0));
    console.log("Test grille vide");
    const emptyResult = isSolvable(emptyGrid);
    console.log("Résultat grille vide:", emptyResult);
    expect(emptyResult).toBe(true);

    // Grille avec conflit (non résolvable)
    const invalidGrid = Array(9).fill(null).map(() => Array(9).fill(0));
    invalidGrid[0][0] = 5;
    invalidGrid[0][1] = 5;
    console.log("Test grille invalide");
    const invalidResult = isSolvable(invalidGrid);
    console.log("Résultat grille invalide:", invalidResult);
    expect(invalidResult).toBe(false);
    console.log("Fin du test isSolvable");
  });

  test("generateSudoku génère une grille valide pour le niveau FACILE", () => {
    console.log("Début du test generateSudoku");
    const grid = generateSudoku("FACILE");
    console.log("Grille générée");

    // Vérifier les dimensions de la grille
    expect(grid.length).toBe(9);
    grid.forEach(row => expect(row.length).toBe(9));
    console.log("Dimensions vérifiées");

    // Vérifier le nombre de cases vides
    const emptyCells = grid.flat().filter(cell => cell === 0).length;
    console.log("Nombre de cases vides:", emptyCells);
    expect(emptyCells).toBe(CELLS_TO_REMOVE["FACILE"]);

    // Vérifier que la grille est résolvable
    console.log("Vérification de la résolvabilité");
    expect(isSolvable(grid)).toBe(true);
    console.log("Fin du test generateSudoku");
  });
});

describe("Fonctions de vérification de complétion", () => {
  test("isLineComplete détecte correctement les lignes complètes", () => {
    console.log("Début du test isLineComplete");
    const grid = Array(9).fill(null).map(() => Array(9).fill(1));
    expect(isLineComplete(grid, 0)).toBe(true);

    grid[0][0] = 0;
    expect(isLineComplete(grid, 0)).toBe(false);
    console.log("Fin du test isLineComplete");
  });

  test("isColumnComplete détecte correctement les colonnes complètes", () => {
    console.log("Début du test isColumnComplete");
    const grid = Array(9).fill(null).map(() => Array(9).fill(1));
    expect(isColumnComplete(grid, 0)).toBe(true);

    grid[0][0] = 0;
    expect(isColumnComplete(grid, 0)).toBe(false);
    console.log("Fin du test isColumnComplete");
  });

  test("isBlockComplete détecte correctement les blocs complets", () => {
    console.log("Début du test isBlockComplete");
    const grid = Array(9).fill(null).map(() => Array(9).fill(1));
    expect(isBlockComplete(grid, 0)).toBe(true);

    grid[0][0] = 0;
    expect(isBlockComplete(grid, 0)).toBe(false);
    console.log("Fin du test isBlockComplete");
  });
}); 