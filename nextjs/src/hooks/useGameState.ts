'use client';

import { useState, useEffect } from 'react';
import { generateSudoku, isSolvable } from '@/lib/sudoku-generator';
import { DifficultyLevel } from '@/types/difficulty';

// Constantes pour le calcul du score
const SCORE_CONFIG = {
  BASE_CELL_POINTS: 100,
  ERROR_PENALTY: 50,
  LINE_COMPLETION_BONUS: 500,
  COLUMN_COMPLETION_BONUS: 500,
  BLOCK_COMPLETION_BONUS: 500,
  VICTORY_BONUS: 2000,
  TIME_PENALTY_INTERVAL: 30,
  MAX_ERRORS: 3,
} as const;

export interface GameState {
  grid: number[][];
  initialGrid: boolean[][];
  selectedCell: { row: number; col: number } | null;
  relatedCells: { row: number; col: number }[];
  errorCells: { row: number; col: number }[];
  isComplete: boolean;
  isPlaying: boolean;
  timeElapsed: number;
  score: number;
  errorCount: number;
  disabledNumbers: number[];
  handleCellSelect: (row: number, col: number) => void;
  handleNumberSelect: (number: number) => void;
}

export function useGameState(difficulty: DifficultyLevel): GameState {
  // Générer la grille initiale
  const initialSudoku = generateSudoku(difficulty);
  const initialBooleanGrid = initialSudoku.map(row => row.map(cell => cell !== 0));
  
  // Calculer les nombres désactivés initiaux
  const getInitialDisabledNumbers = () => {
    const disabled: number[] = [];
    for (let num = 1; num <= 9; num++) {
      let count = 0;
      for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {
          if (initialSudoku[i][j] === num) count++;
        }
      }
      if (count >= 9) disabled.push(num);
    }
    return disabled;
  };

  // État du jeu
  const [grid, setGrid] = useState<number[][]>(initialSudoku);
  const [initialGrid] = useState<boolean[][]>(initialBooleanGrid);
  const [selectedCell, setSelectedCell] = useState<{ row: number; col: number } | null>(null);
  const [relatedCells, setRelatedCells] = useState<{ row: number; col: number }[]>([]);
  const [errorCells, setErrorCells] = useState<{ row: number; col: number }[]>([]);
  const [isComplete, setIsComplete] = useState(false);
  const [isPlaying, setIsPlaying] = useState(true);
  const [startTime] = useState<Date>(new Date());
  const [currentTime, setCurrentTime] = useState<Date>(new Date());
  const timeElapsed = Math.floor((currentTime.getTime() - startTime.getTime()) / 1000);
  const [score, setScore] = useState(0);
  const [errorCount, setErrorCount] = useState(0);
  const [disabledNumbers, setDisabledNumbers] = useState<number[]>(getInitialDisabledNumbers());

  useEffect(() => {
    let intervalId: ReturnType<typeof setInterval>;

    if (isPlaying) {
      intervalId = setInterval(() => {
        setCurrentTime(new Date());
      }, 1000);
    }

    return () => {
      if (intervalId) clearInterval(intervalId);
    };
  }, [isPlaying]);

  // Fonctions utilitaires mémorisées
  const isSameBlock = (row1: number, col1: number, row2: number, col2: number): boolean => {
    const blockRow1 = Math.floor(row1 / 3);
    const blockCol1 = Math.floor(col1 / 3);
    const blockRow2 = Math.floor(row2 / 3);
    const blockCol2 = Math.floor(col2 / 3);
    return blockRow1 === blockRow2 && blockCol1 === blockCol2;
  };

  const getRelatedCells = (row: number, col: number): { row: number; col: number }[] => {
    const related: { row: number; col: number }[] = [];
    const value = grid[row][col];

    for (let i = 0; i < 9; i++) {
      for (let j = 0; j < 9; j++) {
        if (
          i === row ||
          j === col ||
          isSameBlock(i, j, row, col) ||
          (value !== 0 && grid[i][j] === value)
        ) {
          related.push({ row: i, col: j });
        }
      }
    }
    return related;
  };

  const isNumberValid = (row: number, col: number, num: number): boolean => {
    for (let j = 0; j < 9; j++) {
      if (j !== col && grid[row][j] === num) return false;
    }

    for (let i = 0; i < 9; i++) {
      if (i !== row && grid[i][col] === num) return false;
    }

    const blockRow = Math.floor(row / 3) * 3;
    const blockCol = Math.floor(col / 3) * 3;
    for (let i = blockRow; i < blockRow + 3; i++) {
      for (let j = blockCol; j < blockCol + 3; j++) {
        if ((i !== row || j !== col) && grid[i][j] === num) return false;
      }
    }

    return true;
  };

  const updateScore = (points: number) => {
    const timeMultiplier = Math.max(0, 100 - Math.floor(timeElapsed / SCORE_CONFIG.TIME_PENALTY_INTERVAL)) / 100;
    const adjustedPoints = Math.floor(points * timeMultiplier);
    setScore(prev => prev + adjustedPoints);
  };

  const checkCompletions = (row: number, col: number) => {
    let bonus = 0;
    
    const isLineComplete = (row: number): boolean => {
      const values = new Set(grid[row]);
      return values.size === 9 && !values.has(0);
    };

    const isColumnComplete = (col: number): boolean => {
      const values = new Set(grid.map(row => row[col]));
      return values.size === 9 && !values.has(0);
    };

    const isBlockComplete = (blockIndex: number): boolean => {
      const blockRow = Math.floor(blockIndex / 3) * 3;
      const blockCol = (blockIndex % 3) * 3;
      const values = new Set();
      
      for (let i = blockRow; i < blockRow + 3; i++) {
        for (let j = blockCol; j < blockCol + 3; j++) {
          values.add(grid[i][j]);
        }
      }
      
      return values.size === 9 && !values.has(0);
    };
    
    if (isLineComplete(row)) {
      bonus += SCORE_CONFIG.LINE_COMPLETION_BONUS;
    }
    
    if (isColumnComplete(col)) {
      bonus += SCORE_CONFIG.COLUMN_COMPLETION_BONUS;
    }
    
    const blockIndex = Math.floor(row / 3) * 3 + Math.floor(col / 3);
    if (isBlockComplete(blockIndex)) {
      bonus += SCORE_CONFIG.BLOCK_COMPLETION_BONUS;
    }
    
    if (bonus > 0) {
      updateScore(bonus);
    }
  };

  // Gestionnaires d'événements
  const handleCellSelect = (row: number, col: number) => {
    if (!isPlaying || errorCount >= SCORE_CONFIG.MAX_ERRORS) return;
    
    // Si on avait une cellule sélectionnée en erreur, on la nettoie
    if (selectedCell && errorCells.some(cell => cell.row === selectedCell.row && cell.col === selectedCell.col)) {
      setGrid(prev => {
        const newGrid = prev.map(r => [...r]);
        newGrid[selectedCell.row][selectedCell.col] = 0;
        return newGrid;
      });
      setErrorCells(prev => prev.filter(cell => cell.row !== selectedCell.row || cell.col !== selectedCell.col));
    }
    
    setSelectedCell({ row, col });
    setRelatedCells(getRelatedCells(row, col));
  };

  const handleNumberSelect = (number: number) => {
    if (!selectedCell || !isPlaying || errorCount >= SCORE_CONFIG.MAX_ERRORS) return;
    // On ne peut pas modifier les cellules initiales
    if (initialGrid[selectedCell.row][selectedCell.col]) return;
    // On ne peut modifier que les cellules vides ou en erreur
    if (grid[selectedCell.row][selectedCell.col] !== 0 && 
        !errorCells.some(cell => cell.row === selectedCell.row && cell.col === selectedCell.col)) return;
    if (disabledNumbers.includes(number)) return;

    const { row, col } = selectedCell;
    
    // On nettoie d'abord l'erreur si elle existe
    if (errorCells.some(cell => cell.row === row && cell.col === col)) {
      setErrorCells(prev => prev.filter(cell => cell.row !== row || cell.col !== col));
    }

    let isValid = isNumberValid(row, col, number);
    
    if (isValid) {
      // Vérifier si le coup rend la grille impossible à résoudre
      const testGrid = grid.map(r => [...r]);
      testGrid[row][col] = number;
      if (!isSolvable(testGrid)) {
        isValid = false;
      }
    }
    
    // Mettre à jour la grille
    setGrid(prev => {
      const newGrid = prev.map(r => [...r]);
      newGrid[row][col] = number;
      
      // Calculer les chiffres désactivés
      const disabled: number[] = [];
      for (let num = 1; num <= 9; num++) {
        let count = 0;
        for (let i = 0; i < 9; i++) {
          for (let j = 0; j < 9; j++) {
            if (newGrid[i][j] === num) count++;
          }
        }
        if (count >= 9) disabled.push(num);
      }
      setDisabledNumbers(disabled);
      
      return newGrid;
    });
    
    setRelatedCells(getRelatedCells(row, col));
    
    if (isValid) {
      setErrorCells(prev => prev.filter(cell => cell.row !== row || cell.col !== col));
      updateScore(SCORE_CONFIG.BASE_CELL_POINTS);
      checkCompletions(row, col);
      
      setGrid(prev => {
        const isGridComplete = prev.every((row, i) => 
          row.every((cell, j) => 
            cell !== 0 && !errorCells.some(err => err.row === i && err.col === j)
          )
        );
        if (isGridComplete) {
          setIsComplete(true);
          setIsPlaying(false);
          updateScore(SCORE_CONFIG.VICTORY_BONUS);
        }
        return prev;
      });
    } else {
      setErrorCells(prev => [...prev.filter(cell => cell.row !== row || cell.col !== col), { row, col }]);
      setErrorCount(prev => {
        const newCount = prev + 1;
        if (newCount >= SCORE_CONFIG.MAX_ERRORS) {
          setIsPlaying(false);
        }
        return newCount;
      });
      updateScore(-SCORE_CONFIG.ERROR_PENALTY);
    }
  };

  return {
    grid,
    initialGrid,
    selectedCell,
    relatedCells,
    errorCells,
    isComplete,
    isPlaying,
    timeElapsed,
    score,
    errorCount,
    disabledNumbers,
    handleCellSelect,
    handleNumberSelect,
  };
} 