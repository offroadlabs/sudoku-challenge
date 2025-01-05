#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "screen.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <vector>
#include <QTimer>
#include "../core/cell.h"
#include "../core/sudoku.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

/**
 * @brief Écran principal de jeu
 *
 * Gère l'affichage et l'interaction avec la grille de Sudoku,
 * le chronomètre, le score et les contrôles de jeu.
 */
class GameScreen : public Screen
{
    Q_OBJECT

public:
    // Constantes pour le calcul du score
    static constexpr int BASE_CELL_POINTS = 100;        ///< Points de base pour une cellule correcte
    static constexpr int ERROR_PENALTY = 50;            ///< Pénalité pour une erreur
    static constexpr int LINE_COMPLETION_BONUS = 500;   ///< Bonus pour une ligne complète
    static constexpr int COLUMN_COMPLETION_BONUS = 500; ///< Bonus pour une colonne complète
    static constexpr int BLOCK_COMPLETION_BONUS = 500;  ///< Bonus pour un bloc complet
    static constexpr int VICTORY_BONUS = 2000;          ///< Bonus de victoire
    static constexpr int TIME_PENALTY_INTERVAL = 30;    ///< Intervalle en secondes pour la diminution des points

    /**
     * @brief Constructeur
     * @param difficulty Niveau de difficulté choisi
     * @param parent Widget parent
     */
    explicit GameScreen(const QString &difficulty, QWidget *parent = nullptr);
    /**
     * @brief Réinitialise le jeu avec un nouveau niveau de difficulté
     * @param difficulty Nouveau niveau de difficulté
     *
     * Réinitialise le score, le temps, les erreurs et génère une nouvelle grille
     */
    void resetGame(const QString &difficulty);

protected:
    /**
     * @brief Filtre les événements pour gérer les interactions clavier/souris
     * @param obj Objet recevant l'événement
     * @param event Événement à traiter
     * @return true si l'événement a été traité, false sinon
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    /**
     * @brief Configure la grille de jeu initiale
     */
    void setupGrid();

    /**
     * @brief Configure les boutons numériques (1-9)
     */
    void setupNumberButtons();

    /**
     * @brief Met à jour la cellule sélectionnée
     * @param cell Nouvelle cellule sélectionnée
     */
    void updateSelectedCell(QLabel *cell);

    /**
     * @brief Configure la barre d'état (score, temps, erreurs)
     */
    void setupStatusBar();

    /**
     * @brief Met à jour l'affichage du chronomètre
     */
    void updateTimer();

    /**
     * @brief Configure un bloc 3x3 de la grille
     * @param blockWidget Widget conteneur du bloc
     * @param blockRow Ligne du bloc (0-2)
     * @param blockCol Colonne du bloc (0-2)
     */
    void setupBlock(QWidget *blockWidget, int blockRow, int blockCol);

    /**
     * @brief Met en surbrillance les cellules liées
     * @param selectedCell Cellule sélectionnée
     * @param highlight true pour activer la surbrillance, false pour la désactiver
     */
    void highlightRelatedCells(QLabel *selectedCell, bool highlight);

    /**
     * @brief Vérifie si deux cellules sont dans le même bloc 3x3
     * @param cell1 Première cellule
     * @param cell2 Deuxième cellule
     * @return true si les cellules sont dans le même bloc
     */
    bool isSameBlock(QLabel *cell1, QLabel *cell2);

    /**
     * @brief Vérifie si deux cellules ont la même valeur
     * @param cell1 Première cellule
     * @param cell2 Deuxième cellule
     * @return true si les cellules ont la même valeur (non vide)
     */
    bool hasSameValue(QLabel *cell1, QLabel *cell2);

    /**
     * @brief Vérifie si un nombre est correct pour une cellule
     * @param cell Cellule à vérifier
     * @param number Nombre à vérifier
     * @return true si le nombre respecte les règles du Sudoku
     */
    bool isNumberCorrect(QLabel *cell, int number);

    /**
     * @brief Met à jour l'affichage de la grille
     */
    void updateGridDisplay();

    /**
     * @brief Convertit une difficulté textuelle en énumération
     * @param difficulty Chaîne de difficulté ("FACILE", "MOYEN", etc.)
     * @return Énumération Sudoku::Difficulty correspondante
     */
    Sudoku::Difficulty difficultyToEnum(const QString &difficulty);

    /**
     * @brief Met à jour le style d'une cellule
     * @param cell Cellule à mettre à jour
     * @param index Index de la cellule dans la grille
     */
    void updateCellStyle(QLabel *cell, int index);

    // Nouvelles méthodes privées
    /**
     * @brief Met à jour le score avec les points donnés
     * @param points Points à ajouter (ou soustraire si négatif)
     */
    void updateScore(int points);

    /**
     * @brief Calcule le multiplicateur de score basé sur le temps
     * @return Pourcentage du multiplicateur (0-100)
     */
    int calculateTimeMultiplier() const;

    /**
     * @brief Vérifie si une ligne est complète
     * @param row Index de la ligne à vérifier
     * @return true si la ligne est complète et valide
     */
    bool isLineComplete(int row) const;

    /**
     * @brief Vérifie si une colonne est complète
     * @param col Index de la colonne à vérifier
     * @return true si la colonne est complète et valide
     */
    bool isColumnComplete(int col) const;

    /**
     * @brief Vérifie si un bloc 3x3 est complet
     * @param blockIndex Index du bloc (0-8)
     * @return true si le bloc est complet et valide
     */
    bool isBlockComplete(int blockIndex) const;

    /**
     * @brief Vérifie les complétions après un placement
     * @param row Ligne du dernier placement
     * @param col Colonne du dernier placement
     */
    void checkCompletions(int row, int col);

    /**
     * @brief Compte les occurrences d'un nombre dans la grille
     * @param number Nombre à compter (1-9)
     * @return Nombre d'occurrences
     */
    int countNumberInGrid(int number) const;

    /**
     * @brief Met à jour l'état des boutons numériques
     *
     * Active/désactive les boutons selon la disponibilité des nombres
     */
    void updateNumberButtonStates();

    /**
     * @brief Crée l'animation de victoire
     */
    void createVictoryAnimation();

    /**
     * @brief Démarre l'animation de victoire
     */
    void startVictoryAnimation();

    /**
     * @brief Appelé à la fin de l'animation de victoire
     */
    void onVictoryAnimationFinished();

    /**
     * @brief Vérifie si la grille est entièrement remplie
     * @return true si toutes les cellules sont remplies, false sinon
     */
    bool isGridComplete();

    QGridLayout *m_gridLayout;                        ///< Layout de la grille de jeu
    std::vector<QLabel *> m_cells;                    ///< Cellules de la grille
    std::vector<QPushButton *> m_numberButtons;       ///< Boutons numériques (1-9)
    QLabel *m_selectedCell;                           ///< Cellule actuellement sélectionnée
    QLabel *m_timeLabel;                              ///< Affichage du temps
    QLabel *m_scoreLabel;                             ///< Affichage du score
    QTimer *m_timer;                                  ///< Timer pour le chronomètre
    int m_elapsedSeconds;                             ///< Temps écoulé en secondes
    int m_score;                                      ///< Score actuel
    int m_errorCount;                                 ///< Nombre d'erreurs commises
    QLabel *m_errorLabel;                             ///< Affichage des erreurs
    QString m_difficulty;                             ///< Niveau de difficulté actuel
    QLabel *m_difficultyLabel;                        ///< Affichage de la difficulté
    std::vector<Cell> m_grid;                         ///< État interne de la grille
    QParallelAnimationGroup *m_victoryAnimationGroup; ///< Groupe d'animations de victoire
    bool m_isAnimating;                               ///< Indique si une animation est en cours

private slots:
    /**
     * @brief Gestionnaire d'événement pour les clics sur les boutons numériques
     */
    void onNumberButtonClicked();

signals:
    /**
     * @brief Signal émis à la fin de la partie
     * @param isWin Indique si c'est une victoire
     * @param score Score final
     * @param time Temps total en secondes
     */
    void gameOver(bool isWin, int score, int time);
};

#endif // GAMESCREEN_H