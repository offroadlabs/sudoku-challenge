#ifndef GRID_H
#define GRID_H

#include <array>
#include <vector>

/**
 * @brief Représente une grille complète de Sudoku
 *
 * Cette classe gère une grille 9x9 et fournit des méthodes pour
 * manipuler et valider son contenu selon les règles du Sudoku.
 */
class Grid
{
public:
    static constexpr int SIZE = 9; ///< Taille de la grille (9x9)

    /**
     * @brief Constructeur par défaut
     *
     * Initialise une grille vide
     */
    Grid();

    /**
     * @brief Obtient la valeur d'une cellule
     * @param row Ligne (0-8)
     * @param col Colonne (0-8)
     * @return Valeur de la cellule à la position spécifiée
     */
    int getValue(int row, int col) const;

    /**
     * @brief Définit la valeur d'une cellule
     * @param row Ligne (0-8)
     * @param col Colonne (0-8)
     * @param value Nouvelle valeur (0-9)
     * @return true si la valeur a pu être placée, false sinon
     */
    bool setValue(int row, int col, int value);

    /**
     * @brief Vérifie si la grille respecte les règles du Sudoku
     * @return true si la grille est valide, false sinon
     */
    bool isValid() const;

    /**
     * @brief Vérifie si la grille est complètement résolue
     * @return true si la grille est valide et complète, false sinon
     */
    bool isSolved() const;

    /**
     * @brief Vide la grille
     *
     * Réinitialise toutes les cellules à 0
     */
    void clear();

private:
    /**
     * @brief Vérifie si une valeur est valide dans une ligne
     * @param row Index de la ligne
     * @param value Valeur à vérifier
     * @param skipCol Colonne à ignorer (-1 pour ne rien ignorer)
     * @return true si la valeur est valide dans la ligne
     */
    bool isValidInRow(int row, int value, int skipCol = -1) const;

    /**
     * @brief Vérifie si une valeur est valide dans une colonne
     * @param col Index de la colonne
     * @param value Valeur à vérifier
     * @param skipRow Ligne à ignorer (-1 pour ne rien ignorer)
     * @return true si la valeur est valide dans la colonne
     */
    bool isValidInColumn(int col, int value, int skipRow = -1) const;

    /**
     * @brief Vérifie si une valeur est valide dans un bloc 3x3
     * @param row Ligne de la cellule
     * @param col Colonne de la cellule
     * @param value Valeur à vérifier
     * @param skip Position à ignorer {-1,-1} pour ne rien ignorer
     * @return true si la valeur est valide dans le bloc
     */
    bool isValidInBox(int row, int col, int value, std::pair<int, int> skip = {-1, -1}) const;

    std::array<std::array<int, SIZE>, SIZE> m_grid; ///< Données de la grille
};

#endif // GRID_H