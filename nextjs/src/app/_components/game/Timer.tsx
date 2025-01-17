"use client";

import { useCallback } from "react";

interface TimerProps {
  timeElapsed: number;
}

export default function Timer({ timeElapsed }: TimerProps) {
  const formatTime = useCallback((totalSeconds: number) => {
    const hours = Math.floor(totalSeconds / 3600);
    const minutes = Math.floor((totalSeconds % 3600) / 60);
    const remainingSeconds = totalSeconds % 60;

    const pad = (num: number) => num.toString().padStart(2, "0");

    if (hours > 0) {
      return `${pad(hours)}:${pad(minutes)}:${pad(remainingSeconds)}`;
    }
    return `${pad(minutes)}:${pad(remainingSeconds)}`;
  }, []);

  return (
    <div className="text-2xl font-mono font-bold text-gray-700 mb-4">
      {formatTime(timeElapsed)}
    </div>
  );
}
