import DifficultySelector from "@/app/_components/game/DifficultySelector";

export default async function DifficultyPage() {
  return (
    <div className="min-h-screen flex flex-col px-4">
      <div className="flex-1 flex flex-col items-center justify-center">
        <h1 className="text-3xl sm:text-4xl md:text-5xl font-normal text-blue-500 mb-4 text-center">
          NIVEAU DE DIFFICULTÉ
        </h1>

        <p className="text-base sm:text-lg md:text-xl text-gray-500 mb-12 sm:mb-16 md:mb-20 text-center">
          Choisissez votre défi
        </p>

        <DifficultySelector />
      </div>
    </div>
  );
}
