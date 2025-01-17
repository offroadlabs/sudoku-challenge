import GameBoard from "@/app/_components/game/GameBoard";
import { DifficultyLevel, DIFFICULTY_LEVELS } from "@/types/difficulty";

interface PageProps {
  params: Promise<{ [key: string]: string }>;
  searchParams: Promise<{ [key: string]: string | string[] | undefined }>;
}

function parseDifficulty(value: string | undefined): DifficultyLevel {
  if (!value || !(value in DIFFICULTY_LEVELS)) {
    return DIFFICULTY_LEVELS.MOYEN;
  }
  return value as DifficultyLevel;
}

export default async function GamePage({ searchParams }: PageProps) {
  const params = await searchParams;
  const difficulty = parseDifficulty(params.difficulty as string);

  return (
    <div className="min-h-screen flex items-center justify-center">
      <GameBoard difficulty={difficulty} />
    </div>
  );
}
