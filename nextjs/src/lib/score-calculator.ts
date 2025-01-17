export const SCORE_CONFIG = {
  BASE_CELL_POINTS: 100,        // Points de base pour une cellule correcte
  ERROR_PENALTY: 50,            // Pénalité pour une erreur
  LINE_COMPLETION_BONUS: 500,   // Bonus pour une ligne complète
  COLUMN_COMPLETION_BONUS: 500, // Bonus pour une colonne complète
  BLOCK_COMPLETION_BONUS: 500,  // Bonus pour un bloc complet
  VICTORY_BONUS: 2000,         // Bonus de victoire
  TIME_PENALTY_INTERVAL: 30,    // Intervalle en secondes pour la diminution des points
  MIN_TIME_MULTIPLIER: 20,      // Multiplicateur minimum en pourcentage
} as const;

export function calculateTimeMultiplier(elapsedSeconds: number): number {
  // Le multiplicateur commence à 100% et diminue de 5% toutes les 30 secondes
  const timeMultiplier = 100 - Math.floor(elapsedSeconds / SCORE_CONFIG.TIME_PENALTY_INTERVAL) * 5;
  return Math.max(timeMultiplier, SCORE_CONFIG.MIN_TIME_MULTIPLIER);
}

export function calculateCellPoints(timeMultiplier: number): number {
  return Math.floor(SCORE_CONFIG.BASE_CELL_POINTS * timeMultiplier / 100);
}

export function calculateCompletionBonus(type: 'line' | 'column' | 'block', timeMultiplier: number): number {
  const baseBonus = type === 'line' 
    ? SCORE_CONFIG.LINE_COMPLETION_BONUS 
    : type === 'column' 
      ? SCORE_CONFIG.COLUMN_COMPLETION_BONUS 
      : SCORE_CONFIG.BLOCK_COMPLETION_BONUS;
  
  return Math.floor(baseBonus * timeMultiplier / 100);
}

export function calculateVictoryBonus(timeMultiplier: number): number {
  return Math.floor(SCORE_CONFIG.VICTORY_BONUS * timeMultiplier / 100);
}

export function calculateErrorPenalty(): number {
  return -SCORE_CONFIG.ERROR_PENALTY;
}

type Grid = number[][];

export function isLineComplete(grid: Grid, row: number): boolean {
  for (let col = 0; col < 9; col++) {
    if (grid[row][col] === 0) return false;
  }
  return true;
}

export function isColumnComplete(grid: Grid, col: number): boolean {
  for (let row = 0; row < 9; row++) {
    if (grid[row][col] === 0) return false;
  }
  return true;
}

export function isBlockComplete(grid: Grid, blockIndex: number): boolean {
  const startRow = Math.floor(blockIndex / 3) * 3;
  const startCol = (blockIndex % 3) * 3;

  for (let row = startRow; row < startRow + 3; row++) {
    for (let col = startCol; col < startCol + 3; col++) {
      if (grid[row][col] === 0) return false;
    }
  }
  return true;
}

export function checkCompletions(grid: Grid, row: number, col: number, timeMultiplier: number): number {
  let bonus = 0;

  // Vérifier la ligne
  if (isLineComplete(grid, row)) {
    bonus += calculateCompletionBonus('line', timeMultiplier);
  }

  // Vérifier la colonne
  if (isColumnComplete(grid, col)) {
    bonus += calculateCompletionBonus('column', timeMultiplier);
  }

  // Vérifier le bloc
  const blockIndex = Math.floor(row / 3) * 3 + Math.floor(col / 3);
  if (isBlockComplete(grid, blockIndex)) {
    bonus += calculateCompletionBonus('block', timeMultiplier);
  }

  return bonus;
} 