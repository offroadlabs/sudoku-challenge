"use client";

import { useRouter } from "next/navigation";
import {
  DIFFICULTY_LEVELS,
  DIFFICULTY_DESCRIPTIONS,
  DifficultyKey,
} from "@/types/difficulty";

export default function DifficultySelector() {
  const router = useRouter();

  const handleDifficultySelect = (level: DifficultyKey) => {
    router.push(`/game?difficulty=${level}`);
  };

  return (
    <div className="w-full max-w-[400px] flex flex-col gap-8 sm:gap-10 md:gap-12">
      {(Object.keys(DIFFICULTY_LEVELS) as DifficultyKey[]).map((level) => (
        <div key={level} className="flex flex-col items-center">
          <button
            onClick={() => handleDifficultySelect(level)}
            className="w-full h-14 sm:h-16 md:h-[70px] text-lg sm:text-xl md:text-2xl font-normal 
                     text-white bg-[#2487C7] hover:bg-[#1F78B4] active:bg-[#1A69A1]
                     border-none focus:outline-none"
          >
            {level}
          </button>
          <p className="mt-2 text-sm sm:text-base md:text-lg text-gray-500 text-center">
            {DIFFICULTY_DESCRIPTIONS[level]}
          </p>
        </div>
      ))}
    </div>
  );
}
