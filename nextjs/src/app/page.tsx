import StartButton from "./_components/home/StartButton";

export default async function HomePage() {
  return (
    <div className="min-h-screen flex flex-col px-4">
      <div className="flex-1 flex flex-col items-center justify-center">
        <h1 className="text-4xl sm:text-5xl md:text-6xl font-normal text-blue-500 mb-4 text-center">
          SUDOKU
        </h1>
        <p className="text-lg sm:text-xl md:text-2xl text-blue-500 mb-16 sm:mb-20 md:mb-24 text-center">
          Exercez votre esprit logique
        </p>

        <StartButton />
      </div>

      <div className="py-4 text-center text-sm sm:text-base text-gray-500">
        v1.0.0
      </div>
    </div>
  );
}
