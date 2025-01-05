#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "screen.h"
#include <QLabel>
#include <QPushButton>

/**
 * @brief Écran de fin de partie
 *
 * Affiche le résultat de la partie (victoire/défaite),
 * le score final et le temps de jeu.
 */
class GameOverScreen : public Screen
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur
     * @param isWin Indique si c'est une victoire
     * @param score Score final
     * @param time Temps total en secondes
     * @param parent Widget parent
     */
    explicit GameOverScreen(bool isWin, int score, int time, QWidget *parent = nullptr);

    /**
     * @brief Met à jour les statistiques affichées
     * @param isWin Indique si c'est une victoire
     * @param score Nouveau score
     * @param time Nouveau temps
     */
    void updateStats(bool isWin, int score, int time);

signals:
    /**
     * @brief Signal émis pour démarrer une nouvelle partie
     */
    void newGameClicked();

    /**
     * @brief Signal émis pour retourner à l'accueil
     */
    void backToHomeClicked();

private:
    QLabel *m_titleLabel;         ///< Titre (Victoire/Défaite)
    QPushButton *m_newGameButton; ///< Bouton nouvelle partie
};

#endif // GAMEOVERSCREEN_H