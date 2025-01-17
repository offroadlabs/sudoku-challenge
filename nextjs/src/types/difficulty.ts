export const DIFFICULTY_LEVELS = {
  FACILE: "FACILE",
  MOYEN: "MOYEN",
  DIFFICILE: "DIFFICILE",
  EXPERT: "EXPERT",
} as const;

export type DifficultyKey = keyof typeof DIFFICULTY_LEVELS;
export type DifficultyLevel = typeof DIFFICULTY_LEVELS[DifficultyKey];

export const CELLS_TO_REMOVE: Record<DifficultyKey, number> = {
  FACILE: 40,
  MOYEN: 45,
  DIFFICILE: 50,
  EXPERT: 55,
} as const;

export const DIFFICULTY_DESCRIPTIONS: Record<DifficultyKey, string> = {
  FACILE: "Parfait pour débuter",
  MOYEN: "Pour les joueurs réguliers",
  DIFFICILE: "Un vrai défi",
  EXPERT: "Pour les maîtres du Sudoku",
} as const; 