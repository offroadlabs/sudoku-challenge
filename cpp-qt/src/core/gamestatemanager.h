#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <QObject>
#include "sudoku.h"

/**
 * @brief Gestionnaire d'état global du jeu
 *
 * Implémente le pattern Singleton pour gérer l'état global du jeu,
 * les transitions entre les écrans et le stockage des données de la partie en cours.
 */
class GameStateManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief États possibles du jeu
     */
    enum class GameState
    {
        HOME,                 ///< Écran d'accueil
        DIFFICULTY_SELECTION, ///< Sélection de la difficulté
        PLAYING,              ///< Partie en cours
        GAME_OVER             ///< Fin de partie
    };

    /**
     * @brief Obtient l'instance unique du gestionnaire
     * @return Référence vers l'instance unique
     */
    static GameStateManager &getInstance();

    /**
     * @brief Obtient l'état actuel du jeu
     * @return État actuel
     */
    GameState currentState() const { return m_currentState; }

    /**
     * @brief Obtient le niveau de difficulté actuel
     * @return Chaîne représentant la difficulté
     */
    QString difficulty() const { return m_difficulty; }

    /**
     * @brief Obtient le score actuel
     * @return Score de la partie en cours
     */
    int score() const { return m_score; }

    /**
     * @brief Obtient le temps écoulé
     * @return Temps en secondes
     */
    int time() const { return m_time; }

    /**
     * @brief Indique si la partie est gagnée
     * @return true si victoire, false sinon
     */
    bool isWin() const { return m_isWin; }

public slots:
    /**
     * @brief Démarre une nouvelle partie
     */
    void startNewGame();

    /**
     * @brief Sélectionne un niveau de difficulté
     * @param difficulty Niveau choisi
     */
    void selectDifficulty(const QString &difficulty);

    /**
     * @brief Termine la partie en cours
     * @param isWin Indique si c'est une victoire
     * @param score Score final
     * @param time Temps total
     */
    void endGame(bool isWin, int score, int time);

    /**
     * @brief Retourne à l'écran d'accueil
     */
    void returnToHome();

signals:
    /**
     * @brief Signal émis lors d'un changement d'état
     * @param newState Nouvel état
     */
    void stateChanged(GameState newState);

    /**
     * @brief Signal émis lors d'un changement de difficulté
     * @param difficulty Nouvelle difficulté
     */
    void difficultyChanged(const QString &difficulty);

    /**
     * @brief Signal émis à la fin d'une partie
     * @param isWin Indique si c'est une victoire
     * @param score Score final
     * @param time Temps total
     */
    void gameEnded(bool isWin, int score, int time);

private:
    GameStateManager(QObject *parent = nullptr);
    GameStateManager(const GameStateManager &) = delete;
    GameStateManager &operator=(const GameStateManager &) = delete;

    GameState m_currentState;
    QString m_difficulty;
    int m_score;
    int m_time;
    bool m_isWin;
};

#endif // GAMESTATEMANAGER_H