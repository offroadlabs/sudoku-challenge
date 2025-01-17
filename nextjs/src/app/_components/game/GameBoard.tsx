"use client";

import { useState } from "react";
import { useRouter } from "next/navigation";
import SudokuGrid from "./SudokuGrid";
import GameContainer from "./GameContainer";
import NumberButtons from "./NumberButtons";
import { useGameState } from "@/hooks/useGameState";
import VictoryAnimation from "./VictoryAnimation";
import { DifficultyLevel, DifficultyKey } from "@/types/difficulty";

const DIFFICULTY_NAMES: Record<DifficultyKey, string> = {
  FACILE: "FACILE",
  MOYEN: "MOYEN",
  DIFFICILE: "DIFFICILE",
  EXPERT: "EXPERT",
} as const;

interface GameBoardProps {
  difficulty: DifficultyLevel;
}

export default function GameBoard({ difficulty }: GameBoardProps) {
  const router = useRouter();
  const difficultyKey = difficulty as DifficultyKey;
  const [showModal, setShowModal] = useState(false);

  const {
    grid,
    initialGrid,
    selectedCell,
    relatedCells,
    errorCells,
    disabledNumbers,
    score,
    timeElapsed,
    errorCount,
    isComplete,
    isPlaying,
    handleCellSelect,
    handleNumberSelect,
  } = useGameState(difficulty);

  const handleVictoryAnimationComplete = () => {
    setShowModal(true);
  };

  return (
    <div className="w-full max-w-[90vw] xl:max-w-[1400px] px-4 py-8">
      <GameContainer
        level={DIFFICULTY_NAMES[difficultyKey]}
        time={timeElapsed}
        errors={errorCount}
        score={score}
      >
        <SudokuGrid
          grid={grid}
          initialGrid={initialGrid}
          selectedCell={selectedCell}
          relatedCells={relatedCells}
          errorCells={errorCells}
          onCellSelect={handleCellSelect}
        />

        <NumberButtons
          onNumberSelect={handleNumberSelect}
          disabledNumbers={disabledNumbers}
        />
      </GameContainer>

      <VictoryAnimation
        isVisible={isComplete}
        onAnimationComplete={handleVictoryAnimationComplete}
      />

      {(showModal || (!isPlaying && !isComplete)) && (
        <div className="fixed inset-0 bg-black/60 backdrop-blur-sm flex items-center justify-center p-4">
          <div className="bg-white rounded-3xl overflow-hidden w-full max-w-sm shadow-2xl transform transition-all">
            <div
              className={`p-8 text-center relative ${
                isComplete ? "bg-[#9EC33A]" : "bg-red-500"
              }`}
            >
              <div className="absolute inset-0 bg-white/10"></div>
              <h2 className="text-3xl font-bold text-white relative">
                {isComplete ? "Félicitations !" : "Partie terminée !"}
              </h2>
            </div>

            <div className="p-8 space-y-6 bg-gradient-to-b from-gray-50 to-white">
              <div className="space-y-4">
                <div className="flex justify-between items-center">
                  <span className="text-gray-500 font-medium">Score final</span>
                  <div className="flex flex-col items-end">
                    <span className="text-2xl font-bold text-[#2487C7]">
                      {score.toLocaleString()}
                    </span>
                    <span className="text-xs text-gray-400">points</span>
                  </div>
                </div>
                <div className="h-px bg-gradient-to-r from-transparent via-gray-200 to-transparent"></div>
                <div className="flex justify-between items-center">
                  <span className="text-gray-500 font-medium">Temps</span>
                  <div className="flex flex-col items-end">
                    <span className="text-2xl font-bold text-[#2487C7]">
                      {Math.floor(timeElapsed / 60)}:
                      {(timeElapsed % 60).toString().padStart(2, "0")}
                    </span>
                    <span className="text-xs text-gray-400">minutes</span>
                  </div>
                </div>
              </div>

              {!isComplete && (
                <div className="text-center">
                  <div className="inline-block px-4 py-2 rounded-full bg-red-50 text-red-500 text-sm font-medium">
                    Vous avez fait trop d&apos;erreurs
                  </div>
                </div>
              )}

              <button
                onClick={() => router.push("/difficulty")}
                className="w-full py-4 px-6 bg-[#2487C7] hover:bg-[#1F78B4] active:bg-[#1A69A1] text-white font-semibold rounded-xl transition-all transform hover:scale-[1.02] focus:outline-none focus:ring-2 focus:ring-[#2487C7] focus:ring-offset-2"
              >
                Nouvelle partie
              </button>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}
