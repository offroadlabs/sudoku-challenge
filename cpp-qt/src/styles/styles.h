#ifndef STYLES_H
#define STYLES_H

#include <QString>

/**
 * @brief Namespace contenant les styles de l'interface utilisateur
 */
namespace Styles
{
    /**
     * @brief Style de la fenêtre principale
     *
     * Définit l'apparence globale de l'application
     */
    const QString WINDOW_STYLE = R"(
    QMainWindow {
        background-color: #f5f7f0;
    }
)";

    /**
     * @brief Style des titres
     *
     * Appliqué aux titres principaux des écrans
     */
    const QString TITLE_STYLE = R"(
    QLabel {
        color: #2487C7;
        font-family: 'Arial', sans-serif;
        font-weight: bold;
        padding: 20px;
    }
)";

    /**
     * @brief Style des boutons principaux
     *
     * Définit l'apparence des boutons d'action importants
     */
    const QString PRIMARY_BUTTON = R"(
    QPushButton {
        background-color: #9EC33A;
        color: white;
        border: none;
        border-radius: 25px;
        padding: 15px 32px;
        font-weight: bold;
        min-width: 200px;
        margin: 10px;
    }
    QPushButton:hover {
        background-color: #8eaf34;
        transform: scale(1.05);
    }
    QPushButton:pressed {
        background-color: #7e9b2e;
    }
)";

    /**
     * @brief Style des boutons de difficulté
     *
     * Apparence spécifique pour les boutons de sélection de niveau
     */
    const QString DIFFICULTY_BUTTON = R"(
    QPushButton {
        background-color: #2487C7;
        color: white;
        border: none;
        border-radius: 25px;
        padding: 15px 32px;
        font-weight: bold;
        min-width: 200px;
        margin: 10px;
    }
    QPushButton:hover {
        background-color: #1f75b0;
        transform: scale(1.05);
    }
    QPushButton:pressed {
        background-color: #1a6698;
    }
)";

    /**
     * @brief Style des cellules de la grille de Sudoku
     *
     * Définit l'apparence des cellules et leurs différents états
     * (initiale, sélectionnée, en surbrillance)
     */
    const QString SUDOKU_CELL = R"(
    QPushButton {
        background-color: #2487C7;
        color: white;
        border: none;
        border-radius: 22px;
        font-weight: bold;
    }
    QPushButton:hover {
        background-color: #1f75b0;
        transform: scale(1.05);
    }
    QPushButton:pressed {
        background-color: #1a6698;
    }
)";

    /**
     * @brief Style des boutons numériques
     *
     * Apparence des boutons de sélection des chiffres (1-9)
     */
    const QString NUMBER_BUTTON = R"(
    QPushButton {
        background-color: #9EC33A;
        color: white;
        border: none;
        border-radius: 25px;
        padding: 15px 32px;
        font-weight: bold;
        min-width: 200px;
        margin: 10px;
    }
    QPushButton:hover {
        background-color: #8eaf34;
        transform: scale(1.05);
    }
    QPushButton:pressed {
        background-color: #7e9b2e;
    }
)";

    /**
     * @brief Style des boutons numériques désactivés
     *
     * Apparence des boutons de chiffres quand ils ne sont pas disponibles
     */
    const QString NUMBER_BUTTON_DISABLED = R"(
    QPushButton {
        background-color: #2487C7;
        color: white;
        border: none;
        border-radius: 25px;
        padding: 15px 32px;
        font-weight: bold;
        min-width: 200px;
        margin: 10px;
    }
    QPushButton:hover {
        background-color: #1f75b0;
        transform: scale(1.05);
    }
    QPushButton:pressed {
        background-color: #1a6698;
    }
)";

}

#endif // STYLES_H