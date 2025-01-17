import { DifficultyLevel, CELLS_TO_REMOVE } from "@/types/difficulty";

// Vérifie si un nombre peut être placé dans une cellule
export function isValidMove(grid: number[][], row: number, col: number, num: number): boolean {
  // Vérifier la ligne
  for (let x = 0; x < 9; x++) {
    if (x !== col && grid[row][x] === num) return false;
  }

  // Vérifier la colonne
  for (let y = 0; y < 9; y++) {
    if (y !== row && grid[y][col] === num) return false;
  }

  // Vérifier le bloc 3x3
  const blockRow = Math.floor(row / 3) * 3;
  const blockCol = Math.floor(col / 3) * 3;
  for (let y = blockRow; y < blockRow + 3; y++) {
    for (let x = blockCol; x < blockCol + 3; x++) {
      if (y !== row && x !== col && grid[y][x] === num) return false;
    }
  }

  return true;
}

// Trouve la prochaine cellule vide
function findEmptyCell(grid: number[][]): [number, number] | null {
  for (let row = 0; row < 9; row++) {
    for (let col = 0; col < 9; col++) {
      if (grid[row][col] === 0) {
        return [row, col];
      }
    }
  }
  return null;
}

// Résout la grille par backtracking
function solve(grid: number[][]): boolean {
  const emptyCell = findEmptyCell(grid);
  if (!emptyCell) return true;

  const [row, col] = emptyCell;
  const numbers = shuffleArray([1, 2, 3, 4, 5, 6, 7, 8, 9]);

  for (const num of numbers) {
    if (isValidMove(grid, row, col, num)) {
      grid[row][col] = num;

      if (solve(grid)) return true;

      grid[row][col] = 0;
    }
  }

  return false;
}

// Mélange un tableau
function shuffleArray<T>(array: T[]): T[] {
  const shuffled = [...array];
  for (let i = shuffled.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [shuffled[i], shuffled[j]] = [shuffled[j], shuffled[i]];
  }
  return shuffled;
}

// Remplit un bloc 3x3 avec des nombres aléatoires
function fillBlock(grid: number[][], blockIndex: number): void {
  const numbers = shuffleArray([1, 2, 3, 4, 5, 6, 7, 8, 9]);
  const blockRow = Math.floor(blockIndex / 3) * 3;
  const blockCol = (blockIndex % 3) * 3;

  let index = 0;
  for (let row = blockRow; row < blockRow + 3; row++) {
    for (let col = blockCol; col < blockCol + 3; col++) {
      grid[row][col] = numbers[index++];
    }
  }
}

// Génère une grille complète
function generateFullGrid(): number[][] {
  const grid = Array(9).fill(null).map(() => Array(9).fill(0));

  // Remplir les blocs diagonaux (qui sont indépendants)
  fillBlock(grid, 0); // Haut gauche
  fillBlock(grid, 4); // Centre
  fillBlock(grid, 8); // Bas droite

  // Résoudre le reste de la grille
  solve(grid);

  return grid;
}

// Vérifie si une grille a une solution unique
function hasUniqueSolution(grid: number[][]): boolean {
  const copy = grid.map(row => [...row]);
  let solutions = 0;
  
  function countSolutions(grid: number[][]): void {
    if (solutions > 1) return;
    
    const emptyCell = findEmptyCell(grid);
    if (!emptyCell) {
      solutions++;
      return;
    }

    const [row, col] = emptyCell;
    for (let num = 1; num <= 9; num++) {
      if (isValidMove(grid, row, col, num)) {
        grid[row][col] = num;
        countSolutions(grid);
        grid[row][col] = 0;
      }
    }
  }

  countSolutions(copy);
  return solutions === 1;
}

// Vérifie si une grille est résolvable
export function isSolvable(grid: number[][]): boolean {
  const copy = grid.map(row => [...row]);
  let iterations = 0;
  const MAX_ITERATIONS = 10000; // Limite pour éviter les boucles infinies

  function solve(grid: number[][]): boolean {
    iterations++;
    if (iterations > MAX_ITERATIONS) return false;

    const emptyCell = findEmptyCell(grid);
    if (!emptyCell) return true;

    const [row, col] = emptyCell;
    for (let num = 1; num <= 9; num++) {
      if (isValidMove(grid, row, col, num)) {
        grid[row][col] = num;
        if (solve(grid)) return true;
        grid[row][col] = 0;
      }
    }
    return false;
  }

  return solve(copy);
}

// Génère une grille de Sudoku selon la difficulté spécifiée
export function generateSudoku(difficulty: DifficultyLevel): number[][] {
  const grid = generateFullGrid();
  const cellsToRemove = CELLS_TO_REMOVE[difficulty];
  
  // Créer un tableau d'indices et le mélanger
  const indices = shuffleArray(Array.from({ length: 81 }, (_, i) => i));
  
  // Essayer de retirer des cellules tout en maintenant une solution unique
  for (const index of indices) {
    const row = Math.floor(index / 9);
    const col = index % 9;
    const backup = grid[row][col];
    
    grid[row][col] = 0;
    
    // Si la grille n'a plus de solution unique, restaurer la valeur
    if (!hasUniqueSolution(grid)) {
      grid[row][col] = backup;
    }
    
    // Si on a retiré assez de cellules, arrêter
    if (grid.flat().filter(cell => cell === 0).length >= cellsToRemove) {
      break;
    }
  }
  
  return grid;
} 