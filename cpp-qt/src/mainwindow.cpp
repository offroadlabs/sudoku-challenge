#include "mainwindow.h"
#include <QScreen>
#include "styles/styles.h"
#include "screens/gamescreen.h"
#include "screens/gameoverscreen.h"
#include "core/gamestatemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_stackedWidget(new QStackedWidget(this)),
      m_homeScreen(new HomeScreen(this)),
      m_difficultyScreen(new DifficultyScreen(this)),
      m_gameScreen(new GameScreen("FACILE", this)),
      m_gameOverScreen(new GameOverScreen(true, 0, 0, this))
{
    setupWindow();

    // Ajouter les écrans au QStackedWidget
    m_stackedWidget->addWidget(m_homeScreen);
    m_stackedWidget->addWidget(m_difficultyScreen);
    m_stackedWidget->addWidget(m_gameScreen);
    m_stackedWidget->addWidget(m_gameOverScreen);

    // Définir le widget central
    setCentralWidget(m_stackedWidget);

    // Connecter les signaux de navigation
    setupConnections();

    setStyleSheet(Styles::WINDOW_STYLE);
    m_stackedWidget->setCurrentWidget(m_homeScreen);
}

void MainWindow::setupWindow()
{
    setWindowTitle("Sudoku");
    resize(500, 800); // Fenêtre légèrement plus grande
    setMinimumSize(500, 800);
    setMaximumSize(500, 800);

    // Centrer la fenêtre
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void MainWindow::setupConnections()
{
    auto &gameManager = GameStateManager::getInstance();

    // Connecter les signaux du gestionnaire d'état
    connect(&gameManager, &GameStateManager::stateChanged,
            this, &MainWindow::onStateChanged);

    // Connecter les signaux des écrans au gestionnaire d'état
    connect(m_homeScreen, &HomeScreen::startClicked,
            &gameManager, &GameStateManager::startNewGame);

    connect(m_difficultyScreen, &DifficultyScreen::difficultySelected,
            [&gameManager](int level)
            {
                QString difficulty;
                switch (level)
                {
                case 0:
                    difficulty = "FACILE";
                    break;
                case 1:
                    difficulty = "MOYEN";
                    break;
                case 2:
                    difficulty = "DIFFICILE";
                    break;
                case 3:
                    difficulty = "EXPERT";
                    break;
                default:
                    difficulty = "FACILE";
                }
                gameManager.selectDifficulty(difficulty);
            });

    connect(m_gameScreen, &GameScreen::gameOver,
            &gameManager, &GameStateManager::endGame);

    connect(m_gameOverScreen, &GameOverScreen::newGameClicked,
            &gameManager, &GameStateManager::startNewGame);

    connect(m_gameOverScreen, &GameOverScreen::backToHomeClicked,
            &gameManager, &GameStateManager::returnToHome);
}

void MainWindow::onStateChanged(GameStateManager::GameState newState)
{
    switch (newState)
    {
    case GameStateManager::GameState::HOME:
        m_stackedWidget->setCurrentWidget(m_homeScreen);
        break;
    case GameStateManager::GameState::DIFFICULTY_SELECTION:
        m_stackedWidget->setCurrentWidget(m_difficultyScreen);
        break;
    case GameStateManager::GameState::PLAYING:
        m_gameScreen->resetGame(GameStateManager::getInstance().difficulty());
        m_stackedWidget->setCurrentWidget(m_gameScreen);
        break;
    case GameStateManager::GameState::GAME_OVER:
        auto &manager = GameStateManager::getInstance();
        m_gameOverScreen->updateStats(manager.isWin(), manager.score(), manager.time());
        m_stackedWidget->setCurrentWidget(m_gameOverScreen);
        break;
    }
}