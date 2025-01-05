#ifndef CELL_H
#define CELL_H

/**
 * @brief Représente une cellule individuelle dans la grille de Sudoku
 *
 * Cette classe gère l'état d'une cellule unique, incluant sa valeur
 * et si elle fait partie des nombres initiaux de la grille.
 */
class Cell
{
public:
    /**
     * @brief Constructeur par défaut
     *
     * Initialise une cellule vide (valeur 0) et non initiale
     */
    Cell() : m_value(0), m_isInitial(false) {}

    /**
     * @brief Obtient la valeur actuelle de la cellule
     * @return La valeur (0-9, où 0 représente une cellule vide)
     */
    int value() const { return m_value; }

    /**
     * @brief Définit la valeur de la cellule
     * @param value Nouvelle valeur (0-9)
     */
    void setValue(int value) { m_value = value; }

    /**
     * @brief Vérifie si la cellule est vide
     * @return true si la cellule est vide (valeur 0), false sinon
     */
    bool isEmpty() const { return m_value == 0; }

    /**
     * @brief Vérifie si la cellule fait partie des nombres initiaux
     * @return true si c'est une valeur initiale, false sinon
     */
    bool isInitial() const { return m_isInitial; }

    /**
     * @brief Définit si la cellule est une valeur initiale
     * @param initial true pour marquer comme initiale, false sinon
     */
    void setInitial(bool initial) { m_isInitial = initial; }

private:
    int m_value;      ///< Valeur de la cellule (0 = vide, 1-9 = valeur)
    bool m_isInitial; ///< Indique si la valeur fait partie de la grille initiale
};

#endif // CELL_H