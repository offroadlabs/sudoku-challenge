"use client";

import { useRouter } from "next/navigation";

export default function StartButton() {
  const router = useRouter();

  return (
    <button
      onClick={() => router.push("/difficulty")}
      className="w-full sm:w-[300px] h-14 sm:h-16 text-white text-xl sm:text-2xl font-normal 
               bg-[#9EC33A] hover:bg-[#8DAF33] active:bg-[#7C9B2D]
               border-none focus:outline-none"
    >
      COMMENCER
    </button>
  );
}
