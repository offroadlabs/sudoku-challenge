"use client";

interface GameContainerProps {
  level: string;
  time: number;
  errors: number;
  score: number;
  children: React.ReactNode;
}

export default function GameContainer({
  level,
  time,
  errors,
  score,
  children,
}: GameContainerProps) {
  return (
    <div className="w-full max-w-[750px] mx-auto">
      {/* Header */}
      <div className="mb-4 grid grid-cols-3 text-center">
        <div className="flex flex-col">
          <span className="text-[#2487C7] text-lg sm:text-xl md:text-2xl">
            NIVEAU
          </span>
          <span className="text-[#9EC33A] text-lg sm:text-xl md:text-2xl">
            {level}
          </span>
        </div>
        <div className="flex flex-col">
          <span className="text-[#2487C7] text-lg sm:text-xl md:text-2xl">
            TEMPS
          </span>
          <span className="text-[#9EC33A] text-lg sm:text-xl md:text-2xl">
            {Math.floor(time / 60)
              .toString()
              .padStart(2, "0")}
            :{(time % 60).toString().padStart(2, "0")}
          </span>
        </div>
        <div className="flex flex-col">
          <span className="text-[#2487C7] text-lg sm:text-xl md:text-2xl">
            ERREURS
          </span>
          <span className="text-[#9EC33A] text-lg sm:text-xl md:text-2xl">
            {errors}/3
          </span>
        </div>
      </div>

      {/* Score */}
      <div className="mb-8 text-center">
        <span className="text-[#2487C7] text-lg sm:text-xl md:text-2xl">
          SCORE
        </span>
        <div className="text-[#9EC33A] text-4xl sm:text-5xl md:text-6xl font-normal">
          {score.toLocaleString()}
        </div>
      </div>

      {/* Grille et boutons */}
      {children}
    </div>
  );
}
