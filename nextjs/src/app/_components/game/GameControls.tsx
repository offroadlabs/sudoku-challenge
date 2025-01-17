"use client";

interface GameControlsProps {
  onNewGame: () => void;
  onCheck: () => void;
  onSolve: () => void;
  onReset: () => void;
}

export default function GameControls({
  onNewGame,
  onCheck,
  onSolve,
  onReset,
}: GameControlsProps) {
  return (
    <div className="flex gap-4 my-4">
      <button
        onClick={onNewGame}
        className="px-4 py-2 bg-blue-500 text-white rounded hover:bg-blue-600 transition-colors"
      >
        Nouvelle partie
      </button>
      <button
        onClick={onCheck}
        className="px-4 py-2 bg-green-500 text-white rounded hover:bg-green-600 transition-colors"
      >
        Vérifier
      </button>
      <button
        onClick={onSolve}
        className="px-4 py-2 bg-yellow-500 text-white rounded hover:bg-yellow-600 transition-colors"
      >
        Solution
      </button>
      <button
        onClick={onReset}
        className="px-4 py-2 bg-red-500 text-white rounded hover:bg-red-600 transition-colors"
      >
        Réinitialiser
      </button>
    </div>
  );
}
