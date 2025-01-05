#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "screen.h"
#include <QLabel>
#include <QPushButton>

/**
 * @brief Écran d'accueil du jeu
 *
 * Affiche le logo, le titre et les options principales du jeu.
 * Premier écran que voit l'utilisateur au lancement de l'application.
 */
class HomeScreen : public Screen
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur
     * @param parent Widget parent
     */
    explicit HomeScreen(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal émis quand le joueur démarre une partie
     */
    void startClicked();

private:
    QLabel *m_titleLabel;       ///< Label du titre principal
    QPushButton *m_startButton; ///< Bouton pour démarrer une partie
};

#endif // HOMESCREEN_H