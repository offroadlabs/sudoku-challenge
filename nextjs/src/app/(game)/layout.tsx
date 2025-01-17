export default function GameLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <main className="min-h-screen bg-gradient-to-b from-blue-50 to-white">
      {children}
    </main>
  );
}
