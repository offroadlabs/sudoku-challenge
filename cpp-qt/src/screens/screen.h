#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QVBoxLayout>

/**
 * @brief Classe de base pour tous les écrans du jeu
 *
 * Fournit une structure commune et des fonctionnalités de base
 * pour tous les écrans de l'application.
 */
class Screen : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur
     * @param parent Widget parent
     *
     * Initialise un layout vertical pour organiser les éléments de l'écran
     */
    explicit Screen(QWidget *parent = nullptr);

    /**
     * @brief Destructeur virtuel
     */
    virtual ~Screen() = default;

protected:
    QVBoxLayout *m_layout; ///< Layout principal de l'écran
};

#endif // SCREEN_H