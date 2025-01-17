"use client";

interface NumberButtonsProps {
  onNumberSelect: (number: number) => void;
  disabledNumbers?: number[];
}

export default function NumberButtons({
  onNumberSelect,
  disabledNumbers = [],
}: NumberButtonsProps) {
  return (
    <div className="flex justify-center gap-1 sm:gap-2 mt-4 sm:mt-6">
      {Array.from({ length: 9 }, (_, i) => i + 1).map((number) => (
        <button
          key={number}
          onClick={() => onNumberSelect(number)}
          disabled={disabledNumbers.includes(number)}
          className={`
            w-12 h-12 sm:w-14 sm:h-14 md:w-16 md:h-16 rounded-full
            text-white text-lg sm:text-xl md:text-2xl font-normal
            ${
              disabledNumbers.includes(number)
                ? "bg-gray-400 cursor-not-allowed"
                : "bg-[#2487C7] hover:bg-[#1F78B4] active:bg-[#1A69A1]"
            }
            focus:outline-none
          `}
        >
          {number}
        </button>
      ))}
    </div>
  );
}
