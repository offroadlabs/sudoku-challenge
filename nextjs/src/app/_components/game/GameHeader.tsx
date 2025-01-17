"use client";

interface GameHeaderProps {
  level: string;
  time: number;
  errors: number;
  score: number;
}

export default function GameHeader({
  level,
  time,
  errors,
  score,
}: GameHeaderProps) {
  const formatTime = (seconds: number) => {
    const minutes = Math.floor(seconds / 60);
    const remainingSeconds = seconds % 60;
    return `${minutes.toString().padStart(2, "0")}:${remainingSeconds
      .toString()
      .padStart(2, "0")}`;
  };

  return (
    <div className="w-full max-w-[400px] mx-auto mb-4">
      {/* Première ligne : Niveau, Temps, Erreurs */}
      <div className="flex justify-between text-xs mb-1">
        <div className="flex flex-col items-center">
          <span className="text-[#2487C7]">NIVEAU</span>
          <span className="text-[#9EC33A] font-normal">NIVEAU: {level}</span>
        </div>

        <div className="flex flex-col items-center">
          <span className="text-[#2487C7]">TEMPS</span>
          <span className="text-[#9EC33A] font-normal">{formatTime(time)}</span>
        </div>

        <div className="flex flex-col items-center">
          <span className="text-[#2487C7]">ERREURS</span>
          <span className="text-[#9EC33A] font-normal">{errors}/3</span>
        </div>
      </div>

      {/* Deuxième ligne : Score */}
      <div className="flex flex-col items-center">
        <span className="text-[#2487C7] text-xs">SCORE</span>
        <span className="text-[#9EC33A] text-2xl font-normal">{score}</span>
      </div>
    </div>
  );
}
