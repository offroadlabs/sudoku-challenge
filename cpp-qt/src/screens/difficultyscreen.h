#ifndef DIFFICULTYSCREEN_H
#define DIFFICULTYSCREEN_H

#include "screen.h"

/**
 * @brief Écran de sélection de la difficulté
 *
 * Permet au joueur de choisir le niveau de difficulté
 * avant de commencer une partie.
 */
class DifficultyScreen : public Screen
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur
     * @param parent Widget parent
     */
    explicit DifficultyScreen(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal émis lors de la sélection d'un niveau
     * @param level Index du niveau choisi (0-3)
     */
    void difficultySelected(int level);
};

#endif // DIFFICULTYSCREEN_H