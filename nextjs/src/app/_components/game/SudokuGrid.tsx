"use client";

import React from "react";

interface SudokuGridProps {
  grid: number[][];
  initialGrid: boolean[][];
  selectedCell?: { row: number; col: number } | null;
  relatedCells?: { row: number; col: number }[];
  onCellSelect?: (row: number, col: number) => void;
  errorCells?: { row: number; col: number }[];
}

export default function SudokuGrid({
  grid,
  initialGrid,
  selectedCell,
  relatedCells = [],
  onCellSelect,
  errorCells = [],
}: SudokuGridProps) {
  const isCellSelected = (row: number, col: number): boolean => {
    return selectedCell?.row === row && selectedCell?.col === col;
  };

  const isCellRelated = (row: number, col: number): boolean => {
    return relatedCells.some((cell) => cell.row === row && cell.col === col);
  };

  const isCellError = (row: number, col: number): boolean => {
    return errorCells.some((cell) => cell.row === row && cell.col === col);
  };

  return (
    <div className="relative aspect-square w-full max-w-[750px] mx-auto">
      {/* Bordure bleue externe */}
      <div className="absolute inset-0 border-2 border-[#2487C7]" />

      {/* Grille principale */}
      <div className="grid grid-cols-9 h-full w-full">
        {grid.map((row, rowIndex) =>
          row.map((cell, colIndex) => {
            // Calculer les bordures épaisses pour les blocs 3x3
            const thickBorderRight = (colIndex + 1) % 3 === 0 && colIndex < 8;
            const thickBorderBottom = (rowIndex + 1) % 3 === 0 && rowIndex < 8;

            // Déterminer les états de la cellule
            const isSelected = isCellSelected(rowIndex, colIndex);
            const isRelated = isCellRelated(rowIndex, colIndex);
            const isInitial = initialGrid[rowIndex][colIndex];
            const isError = isCellError(rowIndex, colIndex);

            return (
              <div
                key={`${rowIndex}-${colIndex}`}
                onClick={() => onCellSelect?.(rowIndex, colIndex)}
                className={`
                  relative flex items-center justify-center
                  w-full h-full
                  cursor-pointer
                  ${
                    isSelected
                      ? "bg-[#2487C7] bg-opacity-20"
                      : isRelated
                      ? "bg-[#2487C7] bg-opacity-10"
                      : ""
                  }
                  border-[0.5px] border-gray-300
                  ${thickBorderRight ? "border-r-2 border-r-[#2487C7]" : ""}
                  ${thickBorderBottom ? "border-b-2 border-b-[#2487C7]" : ""}
                `}
              >
                <span
                  className={`
                    text-2xl sm:text-3xl md:text-4xl font-normal
                    ${
                      isError
                        ? "text-red-500"
                        : isInitial
                        ? "text-[#2487C7]"
                        : "text-[#9EC33A]"
                    }
                  `}
                >
                  {cell === 0 ? "" : cell}
                </span>
              </div>
            );
          })
        )}
      </div>
    </div>
  );
}
