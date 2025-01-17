"use client";

import { motion } from "framer-motion";

interface VictoryAnimationProps {
  isVisible: boolean;
  onAnimationComplete?: () => void;
}

export default function VictoryAnimation({
  isVisible,
  onAnimationComplete,
}: VictoryAnimationProps) {
  if (!isVisible) return null;

  // Créer un tableau de particules
  const particles = Array.from({ length: 100 }, (_, i) => {
    const angle = (i / 100) * Math.PI * 2;
    const radius = Math.random() * 300 + 150;
    return {
      x: Math.cos(angle) * radius,
      y: Math.sin(angle) * radius,
      scale: Math.random() * 1.5 + 0.8,
      rotation: Math.random() * 360,
    };
  });

  return (
    <div className="fixed inset-0 pointer-events-none">
      {/* Première vague de particules */}
      {particles.map((particle, i) => (
        <motion.div
          key={i}
          className="absolute left-1/2 top-1/2 w-8 h-8 rounded-full bg-[#9EC33A]"
          initial={{
            x: 0,
            y: 0,
            scale: 0,
            opacity: 1,
            rotate: 0,
          }}
          animate={{
            x: particle.x,
            y: particle.y,
            scale: particle.scale,
            opacity: 0,
            rotate: particle.rotation,
          }}
          transition={{
            duration: 1.8,
            ease: "easeOut",
            delay: Math.random() * 0.3,
          }}
        />
      ))}

      {/* Deuxième vague de particules plus petites */}
      {particles.map((particle, i) => (
        <motion.div
          key={`small-${i}`}
          className="absolute left-1/2 top-1/2 w-4 h-4 rounded-full bg-[#2487C7]"
          initial={{
            x: 0,
            y: 0,
            scale: 0,
            opacity: 1,
            rotate: 0,
          }}
          animate={{
            x: particle.x * 0.8,
            y: particle.y * 0.8,
            scale: particle.scale * 0.6,
            opacity: 0,
            rotate: particle.rotation,
          }}
          transition={{
            duration: 1.5,
            ease: "easeOut",
            delay: 0.2 + Math.random() * 0.3,
          }}
        />
      ))}

      {/* Effet de flash plus prononcé */}
      <motion.div
        className="absolute inset-0 bg-white"
        initial={{ opacity: 0 }}
        animate={{ opacity: [0, 0.9, 0] }}
        transition={{
          duration: 0.4,
          times: [0, 0.1, 1],
          repeat: 2,
          repeatDelay: 0.2,
        }}
      />

      {/* Cercles concentriques plus grands */}
      {[1, 2, 3, 4].map((_, i) => (
        <motion.div
          key={i}
          className="absolute left-1/2 top-1/2 -translate-x-1/2 -translate-y-1/2 rounded-full border-[6px] border-[#9EC33A]"
          initial={{
            width: 0,
            height: 0,
            opacity: 1,
          }}
          animate={{
            width: 800,
            height: 800,
            opacity: 0,
          }}
          transition={{
            duration: 1.8,
            delay: i * 0.15,
          }}
          onAnimationComplete={i === 3 ? onAnimationComplete : undefined}
        />
      ))}
    </div>
  );
}
