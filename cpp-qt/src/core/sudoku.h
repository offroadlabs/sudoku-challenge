#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include "cell.h"

/**
 * @brief Classe utilitaire pour la gestion et la génération de grilles de Sudoku
 *
 * Cette classe fournit des méthodes statiques pour générer, valider et résoudre
 * des grilles de Sudoku. Elle gère également différents niveaux de difficulté.
 */
class Sudoku
{
public:
    /**
     * @brief Niveaux de difficulté disponibles pour la génération de grilles
     */
    enum class Difficulty
    {
        EASY,   ///< Niveau facile (40 cases vides)
        MEDIUM, ///< Niveau moyen (45 cases vides)
        HARD,   ///< Niveau difficile (50 cases vides)
        EXPERT  ///< Niveau expert (55 cases vides)
    };

    /**
     * @brief Génère une nouvelle grille de Sudoku valide
     * @param difficulty Niveau de difficulté souhaité
     * @return Vecteur de 81 cellules représentant la grille générée
     *
     * Génère une grille complète puis retire un certain nombre de cellules
     * en fonction du niveau de difficulté choisi. Garantit qu'une seule
     * solution existe.
     */
    static std::vector<Cell> generateGrid(Difficulty difficulty = Difficulty::EASY);

    /**
     * @brief Vérifie si un nombre peut être placé à une position donnée
     * @param grid Grille de jeu actuelle
     * @param row Ligne (0-8)
     * @param col Colonne (0-8)
     * @param number Nombre à vérifier (1-9)
     * @return true si le mouvement est valide, false sinon
     *
     * Vérifie les règles du Sudoku : le nombre ne doit pas être présent
     * dans la même ligne, colonne ou bloc 3x3.
     */
    static bool isValidMove(const std::vector<Cell> &grid, int row, int col, int number);

    /**
     * @brief Convertit des coordonnées 2D en index 1D
     * @param row Ligne (0-8)
     * @param col Colonne (0-8)
     * @return Index dans le vecteur de cellules (0-80)
     *
     * Calcule l'index linéaire d'une cellule dans le vecteur à partir
     * de ses coordonnées en tenant compte de la structure en blocs 3x3.
     */
    static int getIndex(int row, int col);

    /**
     * @brief Vérifie si une grille peut être résolue
     * @param grid Grille à vérifier
     * @return true si la grille est résolvable, false sinon
     *
     * Tente de résoudre la grille sans la modifier pour vérifier
     * qu'une solution existe.
     */
    static bool isSolvable(std::vector<Cell> grid);

protected:
    /**
     * @brief Vérifie les conflits pour un nombre dans une position donnée
     * @param grid Grille actuelle
     * @param row Ligne de la position
     * @param col Colonne de la position
     * @param number Nombre à vérifier
     * @return true s'il y a un conflit, false sinon
     */
    static bool hasConflict(const std::vector<Cell> &grid, int row, int col, int number);

    /**
     * @brief Vérifie les conflits dans une ligne
     * @param grid Grille actuelle
     * @param row Ligne à vérifier
     * @param col Colonne à ignorer
     * @param number Nombre à vérifier
     * @return true s'il y a un conflit dans la ligne
     */
    static bool hasRowConflict(const std::vector<Cell> &grid, int row, int col, int number);

    /**
     * @brief Vérifie les conflits dans une colonne
     * @param grid Grille actuelle
     * @param row Ligne à ignorer
     * @param col Colonne à vérifier
     * @param number Nombre à vérifier
     * @return true s'il y a un conflit dans la colonne
     */
    static bool hasColumnConflict(const std::vector<Cell> &grid, int row, int col, int number);

    /**
     * @brief Vérifie les conflits dans un bloc 3x3
     * @param grid Grille actuelle
     * @param row Ligne de la position
     * @param col Colonne de la position
     * @param number Nombre à vérifier
     * @return true s'il y a un conflit dans le bloc
     */
    static bool hasBlockConflict(const std::vector<Cell> &grid, int row, int col, int number);

    /**
     * @brief Trouve la prochaine cellule vide dans la grille
     * @param grid Grille à analyser
     * @return Paire {ligne, colonne} de la cellule vide, {-1, -1} si aucune trouvée
     */
    static std::pair<int, int> findEmptyCell(const std::vector<Cell> &grid);

    /**
     * @brief Résout la grille de Sudoku par backtracking
     * @param grid Grille à résoudre
     * @return true si une solution est trouvée, false sinon
     */
    static bool solve(std::vector<Cell> &grid);

    /**
     * @brief Remplit un bloc 3x3 avec des nombres aléatoires
     * @param grid Grille à modifier
     * @param blockIndex Index du bloc à remplir (0-8)
     */
    static void fillBlock(std::vector<Cell> &grid, int blockIndex);
};

#endif // SUDOKU_H