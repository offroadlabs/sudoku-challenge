import StartButton from "./_components/home/StartButton";
import { BlogIcon } from "./_components/icons/blog-icon";
import { GitHubIcon } from "./_components/icons/github-icon";
import { LinkedInIcon } from "./_components/icons/linkedin-icon";
import { XIcon } from "./_components/icons/x-icon";

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

      <footer className="mt-24 py-12 border-t border-gray-200/40">
        <div className="container mx-auto">
          <div className="flex flex-col items-center gap-8">
            <div className="flex flex-col md:flex-row justify-between items-center w-full gap-6 px-4">
              <div className="flex flex-col items-center md:items-start gap-2">
                <div className="flex items-center gap-2">
                  <a
                    href="https://hub.timoner.com"
                    className="text-lg font-semibold text-blue-500 hover:text-blue-600 transition-colors"
                  >
                    Sébastien TIMONER
                  </a>
                  <span className="text-gray-500">© 2025</span>
                </div>
                <div className="flex items-center justify-center gap-4">
                  <a
                    href="https://github.com/offroadlabs"
                    target="_blank"
                    rel="noopener noreferrer"
                    className="text-gray-500 hover:text-[#9EC33A] transition-colors"
                  >
                    <GitHubIcon className="w-6 h-6" />
                  </a>
                  <a
                    href="https://linkedin.com/in/timoner"
                    target="_blank"
                    rel="noopener noreferrer"
                    className="text-gray-500 hover:text-[#0077B5] transition-colors"
                  >
                    <LinkedInIcon className="w-6 h-6" />
                  </a>
                  <a
                    href="https://twitter.com/sebtimoner"
                    target="_blank"
                    rel="noopener noreferrer"
                    className="text-gray-500 hover:text-[#9EC33A] transition-colors"
                  >
                    <XIcon className="w-6 h-6" />
                  </a>
                  <a
                    href="https://timoner.com"
                    target="_blank"
                    rel="noopener noreferrer"
                    className="text-gray-500 hover:text-[#9EC33A] transition-colors"
                    aria-label="Mon blog"
                  >
                    <BlogIcon className="w-6 h-6" />
                  </a>
                </div>
                <div className="flex items-center gap-2 text-gray-500">
                  <svg
                    xmlns="http://www.w3.org/2000/svg"
                    viewBox="0 0 24 24"
                    fill="currentColor"
                    className="w-4 h-4 text-blue-500"
                  >
                    <path
                      fillRule="evenodd"
                      d="M11.54 22.351l.07.04.028.016a.76.76 0 00.723 0l.028-.015.071-.041a16.975 16.975 0 001.144-.742 19.58 19.58 0 002.683-2.282c1.944-1.99 3.963-4.98 3.963-8.827a8.25 8.25 0 00-16.5 0c0 3.846 2.02 6.837 3.963 8.827a19.58 19.58 0 002.682 2.282 16.975 16.975 0 001.145.742zM12 13.5a3 3 0 100-6 3 3 0 000 6z"
                      clipRule="evenodd"
                    />
                  </svg>
                  <span>Aix-en-Provence</span>
                </div>
              </div>

              <a
                href="https://github.com/offroadlabs/sudoku-challenge"
                target="_blank"
                rel="noopener noreferrer"
                className="flex items-center gap-2 text-gray-500 hover:text-blue-500 transition-colors"
              >
                <GitHubIcon className="w-6 h-6" />
                <span>Code source</span>
              </a>
            </div>
          </div>
        </div>
      </footer>
    </div>
  );
}
