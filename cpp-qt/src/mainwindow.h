#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "screens/homescreen.h"
#include "screens/difficultyscreen.h"
#include "screens/gamescreen.h"
#include "screens/gameoverscreen.h"
#include "core/gamestatemanager.h"

/**
 * @brief Fenêtre principale de l'application
 *
 * Gère la navigation entre les différents écrans et maintient
 * la cohérence de l'interface utilisateur.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur
     * @param parent Widget parent
     */
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    /**
     * @brief Gère les changements d'état du jeu
     * @param newState Nouvel état
     */
    void onStateChanged(GameStateManager::GameState newState);

private:
    /**
     * @brief Configure la fenêtre principale
     */
    void setupWindow();

    /**
     * @brief Configure les connexions signal/slot
     */
    void setupConnections();

    QStackedWidget *m_stackedWidget;      ///< Gestionnaire des écrans
    HomeScreen *m_homeScreen;             ///< Écran d'accueil
    DifficultyScreen *m_difficultyScreen; ///< Écran de sélection de difficulté
    GameScreen *m_gameScreen;             ///< Écran de jeu
    GameOverScreen *m_gameOverScreen;     ///< Écran de fin de partie
};

#endif // MAINWINDOW_H