#include "gamescreen.h"
#include "../styles.h"
#include <QRandomGenerator>
#include <QFont>
#include <QStyle>
#include <QTimer>
#include "../core/sudoku.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>

// Constantes de mise en page
constexpr int GRID_SPACING = 4;    // Espacement entre les blocs de la grille
constexpr int GRID_MARGINS = 4;    // Marges autour de la grille
constexpr int BLOCK_SPACING = 1;   // Espacement entre les cellules d'un bloc
constexpr int BLOCK_MARGINS = 1;   // Marges autour des blocs
constexpr int CELL_SIZE = 50;      // Taille des cellules en pixels
constexpr int CELL_FONT_SIZE = 18; // Taille de la police des cellules

// Constantes pour les boutons de numéros
constexpr int NUMBER_BUTTON_SIZE = 48;     // Taille des boutons de numéros
constexpr int NUMBER_BUTTON_SPACING = 8;   // Espacement entre les boutons
constexpr int NUMBER_BUTTON_MARGIN_H = 20; // Marges horizontales des boutons
constexpr int NUMBER_BUTTON_MARGIN_V = 10; // Marge verticale inférieure des boutons

// Constantes pour la barre d'état
constexpr int STATUS_BAR_SPACING = 5;   // Espacement dans la barre d'état
constexpr int STATUS_BAR_MARGINS = 20;  // Marges de la barre d'état
constexpr int STATUS_BAR_MARGIN_V = 10; // Marges verticales de la barre d'état
constexpr int STATUS_LABEL_SPACING = 2; // Espacement entre les labels
constexpr int STATUS_ROW_SPACING = 20;  // Espacement entre les éléments de la ligne

// Constantes pour les polices
constexpr int STANDARD_LABEL_FONT_SIZE = 10; // Taille de police des labels standards
constexpr int VALUE_LABEL_FONT_SIZE = 16;    // Taille de police des valeurs
constexpr int SCORE_TITLE_FONT_SIZE = 12;    // Taille de police du titre du score
constexpr int SCORE_VALUE_FONT_SIZE = 30;    // Taille de police de la valeur du score

// Constantes pour l'animation
constexpr int FADE_ANIMATION_DURATION = 800; // Durée des animations de fondu en ms
constexpr int DISTANCE_MULTIPLIER = 3;       // Multiplicateur pour la durée de pause

// Constantes pour le jeu
constexpr int MAX_ERRORS = 3;        // Nombre maximum d'erreurs autorisées
constexpr int TIMER_INTERVAL = 1000; // Intervalle de mise à jour du timer en ms

GameScreen::GameScreen(const QString &difficulty, QWidget *parent)
    : Screen(parent), m_gridLayout(new QGridLayout), m_selectedCell(nullptr),
      m_timer(new QTimer(this)),
      m_elapsedSeconds(0),
      m_score(0),
      m_errorCount(0),
      m_difficulty(difficulty),
      m_victoryAnimationGroup(nullptr),
      m_isAnimating(false)
{
    setupStatusBar();

    // Container pour la grille avec marge
    QWidget *gridContainer = new QWidget(this);
    gridContainer->setLayout(m_gridLayout);
    gridContainer->setStyleSheet(
        "QWidget { "
        "background-color: #2487C7; "
        "padding: 0; "
        "border: 0; "
        "}");
    m_layout->addWidget(gridContainer);

    setupGrid();
    setupNumberButtons();

    // Connecter le timer
    connect(m_timer, &QTimer::timeout, this, &GameScreen::updateTimer);
    m_timer->start(1000); // Mise à jour chaque seconde
}

void GameScreen::setupGrid()
{
    // Configuration de la grille principale (3x3 blocs)
    m_gridLayout->setSpacing(GRID_SPACING);
    m_gridLayout->setContentsMargins(GRID_MARGINS, GRID_MARGINS, GRID_MARGINS, GRID_MARGINS);

    // Créer les 9 blocs (3x3)
    for (int blockRow = 0; blockRow < 3; ++blockRow)
    {
        for (int blockCol = 0; blockCol < 3; ++blockCol)
        {
            // Créer un widget pour le bloc
            QWidget *blockWidget = new QWidget(this);
            blockWidget->setStyleSheet(
                "QWidget { "
                "background-color: #9EC33A; " // Fond vert pour les blocs
                "}");

            // Ajouter le bloc à la grille principale
            m_gridLayout->addWidget(blockWidget, blockRow, blockCol);

            // Configurer les cellules dans ce bloc
            setupBlock(blockWidget, blockRow, blockCol);
        }
    }

    // Générer la grille logique
    m_grid = Sudoku::generateGrid(difficultyToEnum(m_difficulty));

    // Mettre à jour l'affichage
    updateGridDisplay();
}

void GameScreen::setupBlock(QWidget *blockWidget, int blockRow, int blockCol)
{
    QGridLayout *blockLayout = new QGridLayout(blockWidget);
    blockLayout->setSpacing(BLOCK_SPACING);
    blockLayout->setContentsMargins(BLOCK_MARGINS, BLOCK_MARGINS, BLOCK_MARGINS, BLOCK_MARGINS);

    for (int cellRow = 0; cellRow < 3; ++cellRow)
    {
        for (int cellCol = 0; cellCol < 3; ++cellCol)
        {
            QLabel *cell = new QLabel(this);

            // Configuration de base
            cell->setFixedSize(CELL_SIZE, CELL_SIZE);
            cell->setAlignment(Qt::AlignCenter);
            cell->setFont(QFont("Arial", CELL_FONT_SIZE, QFont::DemiBold));

            // Position globale
            int globalRow = blockRow * 3 + cellRow;
            int globalCol = blockCol * 3 + cellCol;

            // Propriétés
            cell->setProperty("row", globalRow);
            cell->setProperty("col", globalCol);
            cell->setProperty("initial", false);
            cell->setProperty("selected", false);
            cell->setProperty("related", false);

            // Important: Appliquer le style AVANT d'ajouter au layout
            cell->setStyleSheet(Styles::SUDOKU_CELL);

            // Forcer l'application immédiate du style
            cell->setAttribute(Qt::WA_StyledBackground, true);
            cell->style()->polish(cell);

            // Configuration supplémentaire
            cell->installEventFilter(this);
            cell->setCursor(Qt::PointingHandCursor);
            cell->setText("");

            // Ajouter au layout
            blockLayout->addWidget(cell, cellRow, cellCol);
            m_cells.push_back(cell);
        }
    }
}

void GameScreen::setupNumberButtons()
{
    // Container pour les boutons de numéros
    QWidget *buttonContainer = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setSpacing(NUMBER_BUTTON_SPACING);
    buttonLayout->setContentsMargins(NUMBER_BUTTON_MARGIN_H, NUMBER_BUTTON_MARGIN_H,
                                     NUMBER_BUTTON_MARGIN_H, NUMBER_BUTTON_MARGIN_V);

    // Créer les boutons 1-9
    for (int i = 1; i <= 9; ++i)
    {
        QPushButton *button = new QPushButton(QString::number(i), this);
        button->setFixedSize(NUMBER_BUTTON_SIZE, NUMBER_BUTTON_SIZE);
        button->setFont(QFont("Arial", 18, QFont::DemiBold));
        button->setStyleSheet(Styles::NUMBER_BUTTON);

        // Connecter le signal clicked au slot
        connect(button, &QPushButton::clicked, this, &GameScreen::onNumberButtonClicked);
        button->setProperty("number", i); // Stocker le numéro dans la propriété

        buttonLayout->addWidget(button);
        m_numberButtons.push_back(button);
    }

    m_layout->addWidget(buttonContainer);
}

bool GameScreen::eventFilter(QObject *obj, QEvent *event)
{
    QLabel *cell = qobject_cast<QLabel *>(obj);
    if (cell && m_cells.end() != std::find(m_cells.begin(), m_cells.end(), cell))
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            // On permet toujours la sélection pour le highlight
            updateSelectedCell(cell);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void GameScreen::updateSelectedCell(QLabel *cell)
{
    // Restaurer le style de l'ancienne cellule sélectionnée si elle contenait une erreur
    if (m_selectedCell)
    {
        int row = m_selectedCell->property("row").toInt();
        int col = m_selectedCell->property("col").toInt();
        int index = Sudoku::getIndex(row, col);

        highlightRelatedCells(m_selectedCell, false);
        m_selectedCell->setProperty("selected", false);

        // Si la cellule n'a pas de valeur dans la grille, effacer le texte rouge
        if (m_grid[index].isEmpty())
        {
            m_selectedCell->setText("");
        }

        updateCellStyle(m_selectedCell, index);
    }

    m_selectedCell = cell;
    highlightRelatedCells(cell, true);
    cell->setProperty("selected", true);
    updateCellStyle(cell, Sudoku::getIndex(cell->property("row").toInt(), cell->property("col").toInt()));
}

void GameScreen::highlightRelatedCells(QLabel *selectedCell, bool highlight)
{
    int selectedRow = selectedCell->property("row").toInt();
    int selectedCol = selectedCell->property("col").toInt();
    int selectedIndex = Sudoku::getIndex(selectedRow, selectedCol);
    int selectedValue = m_grid[selectedIndex].value(); // Utiliser la valeur de la grille logique

    for (QLabel *cell : m_cells)
    {
        int row = cell->property("row").toInt();
        int col = cell->property("col").toInt();
        int index = Sudoku::getIndex(row, col);

        bool shouldHighlight =
            row == selectedRow ||                                           // Même ligne
            col == selectedCol ||                                           // Même colonne
            isSameBlock(cell, selectedCell) ||                              // Même bloc 3x3
            (selectedValue != 0 && m_grid[index].value() == selectedValue); // Même valeur (non vide)

        if (shouldHighlight)
        {
            cell->setProperty("related", highlight);
            updateCellStyle(cell, index);
        }
        else if (cell->property("related").toBool())
        {
            cell->setProperty("related", false);
            updateCellStyle(cell, index);
        }
    }
}

bool GameScreen::isSameBlock(QLabel *cell1, QLabel *cell2)
{
    int row1 = cell1->property("row").toInt();
    int col1 = cell1->property("col").toInt();
    int row2 = cell2->property("row").toInt();
    int col2 = cell2->property("col").toInt();

    int block1Row = row1 / 3;
    int block1Col = col1 / 3;
    int block2Row = row2 / 3;
    int block2Col = col2 / 3;

    return (block1Row == block2Row && block1Col == block2Col);
}

bool GameScreen::hasSameValue(QLabel *cell1, QLabel *cell2)
{
    QString value1 = cell1->text();
    QString value2 = cell2->text();
    return !value1.isEmpty() && !value2.isEmpty() && value1 == value2;
}

void GameScreen::setupStatusBar()
{
    // Container pour la barre d'état
    QWidget *statusContainer = new QWidget(this);
    QVBoxLayout *statusLayout = new QVBoxLayout(statusContainer);
    statusLayout->setSpacing(STATUS_BAR_SPACING);
    statusLayout->setContentsMargins(STATUS_BAR_MARGINS, STATUS_BAR_MARGIN_V,
                                     STATUS_BAR_MARGINS, STATUS_BAR_MARGIN_V);

    // Style pour les labels standards (plus petits)
    QString standardLabelStyle =
        "QLabel { "
        "   color: #2487C7; "
        "   font-family: 'Arial'; "
        "   font-size: " +
        QString::number(STANDARD_LABEL_FONT_SIZE) + "px; "
                                                    "   font-weight: normal; "
                                                    "   text-transform: uppercase; "
                                                    "} "
                                                    "QLabel[type=\"value\"] { "
                                                    "   color: #9EC33A; "
                                                    "   font-size: " +
        QString::number(VALUE_LABEL_FONT_SIZE) + "px; "
                                                 "   font-weight: bold; "
                                                 "   letter-spacing: 1px; "
                                                 "}";

    // Style spécial pour le score (plus grand)
    QString scoreLabelStyle =
        "QLabel { "
        "   color: #2487C7; "
        "   font-family: 'Arial'; "
        "   font-size: " +
        QString::number(SCORE_TITLE_FONT_SIZE) + "px; "
                                                 "   font-weight: bold; "
                                                 "} "
                                                 "QLabel[type=\"value\"] { "
                                                 "   color: #9EC33A; "
                                                 "   font-size: " +
        QString::number(SCORE_VALUE_FONT_SIZE) + "px; "
                                                 "   font-weight: bold; "
                                                 "   letter-spacing: 1px; "
                                                 "}";

    // Ligne supérieure : Difficulté, Temps, Erreurs
    QWidget *topRow = new QWidget;
    QHBoxLayout *topRowLayout = new QHBoxLayout(topRow);
    topRowLayout->setSpacing(20);
    topRowLayout->setContentsMargins(0, 0, 0, 0);

    // Difficulté
    QWidget *difficultyWidget = new QWidget;
    QVBoxLayout *difficultyLayout = new QVBoxLayout(difficultyWidget);
    difficultyLayout->setSpacing(2);
    difficultyLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *difficultyTitle = new QLabel("NIVEAU", this);
    difficultyTitle->setAlignment(Qt::AlignCenter);
    m_difficultyLabel = new QLabel(m_difficulty, this);
    m_difficultyLabel->setAlignment(Qt::AlignCenter);
    m_difficultyLabel->setProperty("type", "value");

    difficultyTitle->setStyleSheet(standardLabelStyle);
    m_difficultyLabel->setStyleSheet(standardLabelStyle);

    difficultyLayout->addWidget(difficultyTitle);
    difficultyLayout->addWidget(m_difficultyLabel);

    // Temps
    QWidget *timeWidget = new QWidget;
    QVBoxLayout *timeLayout = new QVBoxLayout(timeWidget);
    timeLayout->setSpacing(2);
    timeLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *timeTitle = new QLabel("TEMPS", this);
    timeTitle->setAlignment(Qt::AlignCenter);
    m_timeLabel = new QLabel("00:00", this);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel->setProperty("type", "value");

    timeTitle->setStyleSheet(standardLabelStyle);
    m_timeLabel->setStyleSheet(standardLabelStyle);

    timeLayout->addWidget(timeTitle);
    timeLayout->addWidget(m_timeLabel);

    // Erreurs
    QWidget *errorWidget = new QWidget;
    QVBoxLayout *errorLayout = new QVBoxLayout(errorWidget);
    errorLayout->setSpacing(2);
    errorLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *errorTitle = new QLabel("ERREURS", this);
    errorTitle->setAlignment(Qt::AlignCenter);
    m_errorLabel = new QLabel("0/3", this);
    m_errorLabel->setAlignment(Qt::AlignCenter);
    m_errorLabel->setProperty("type", "value");

    errorTitle->setStyleSheet(standardLabelStyle);
    m_errorLabel->setStyleSheet(standardLabelStyle);

    errorLayout->addWidget(errorTitle);
    errorLayout->addWidget(m_errorLabel);

    topRowLayout->addWidget(difficultyWidget);
    topRowLayout->addWidget(timeWidget);
    topRowLayout->addWidget(errorWidget);

    // Ligne inférieure : Score
    QWidget *bottomRow = new QWidget;
    QHBoxLayout *bottomRowLayout = new QHBoxLayout(bottomRow);
    bottomRowLayout->setContentsMargins(0, 0, 0, 0);

    // Score
    QWidget *scoreWidget = new QWidget;
    QVBoxLayout *scoreLayout = new QVBoxLayout(scoreWidget);
    scoreLayout->setSpacing(2);
    scoreLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *scoreTitle = new QLabel("SCORE", this);
    scoreTitle->setAlignment(Qt::AlignCenter);
    m_scoreLabel = new QLabel("0", this);
    m_scoreLabel->setAlignment(Qt::AlignCenter);
    m_scoreLabel->setProperty("type", "value");

    scoreTitle->setStyleSheet(scoreLabelStyle);
    m_scoreLabel->setStyleSheet(scoreLabelStyle);

    scoreLayout->addWidget(scoreTitle);
    scoreLayout->addWidget(m_scoreLabel);

    bottomRowLayout->addWidget(scoreWidget);

    // Ajouter les lignes au container principal
    statusLayout->addWidget(topRow);
    statusLayout->addWidget(bottomRow);

    m_layout->addWidget(statusContainer);
}

void GameScreen::updateTimer()
{
    m_elapsedSeconds++;
    int minutes = m_elapsedSeconds / 60;
    int seconds = m_elapsedSeconds % 60;
    m_timeLabel->setText(QString("%1:%2")
                             .arg(minutes, 2, 10, QChar('0'))
                             .arg(seconds, 2, 10, QChar('0')));
}

void GameScreen::updateGridDisplay()
{
    for (int i = 0; i < m_cells.size(); ++i)
    {
        const Cell &cell = m_grid[i];
        QLabel *label = m_cells[i];

        if (cell.isEmpty())
        {
            label->setText("");
        }
        else
        {
            label->setText(QString::number(cell.value()));
        }

        label->setProperty("initial", cell.isInitial());
        label->style()->unpolish(label);
        label->style()->polish(label);
    }
}

void GameScreen::onNumberButtonClicked()
{
    if (!m_selectedCell)
        return;

    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;

    int row = m_selectedCell->property("row").toInt();
    int col = m_selectedCell->property("col").toInt();
    int index = Sudoku::getIndex(row, col);

    // On ne peut pas modifier une cellule initiale ou déjà remplie
    if (m_grid[index].isInitial() || !m_grid[index].isEmpty())
        return;

    int number = button->property("number").toInt();

    // on vérifie si la grille peut être résolue et si elle peut être complétée
    // on copie la grille pour ne pas modifier l'originale
    std::vector<Cell> tempGrid = m_grid;
    tempGrid[index].setValue(number);

    if (!Sudoku::isValidMove(m_grid, row, col, number) || !Sudoku::isSolvable(tempGrid))
    {
        // Pénalité pour une erreur
        updateScore(-ERROR_PENALTY);

        m_errorCount++;
        m_errorLabel->setText(QString("%1/3").arg(m_errorCount));

        m_selectedCell->setText(QString::number(number));
        m_selectedCell->setStyleSheet("QLabel { color: red; background-color: #edf3d8; }");

        if (m_errorCount >= MAX_ERRORS)
        {
            emit gameOver(false, m_score, m_elapsedSeconds);
        }
    }
    else
    {
        // Points pour une cellule correcte
        int timeMultiplier = calculateTimeMultiplier();
        int points = BASE_CELL_POINTS * timeMultiplier / 100;
        updateScore(points);

        m_grid[index].setValue(number);
        m_selectedCell->setText(QString::number(number));
        updateCellStyle(m_selectedCell, index);

        // Mettre à jour l'état des boutons
        updateNumberButtonStates();

        // Vérifier les complétion de lignes/colonnes/blocs
        checkCompletions(row, col);

        if (isGridComplete())
        {
            // Bonus de victoire avec multiplicateur de temps
            int timeMultiplier = calculateTimeMultiplier();
            int victoryPoints = VICTORY_BONUS * timeMultiplier / 100;
            updateScore(victoryPoints);

            // Lancer l'animation au lieu d'émettre directement le signal gameOver
            startVictoryAnimation();
        }
    }
}

bool GameScreen::isGridComplete()
{
    for (const auto &cell : m_grid)
    {
        if (cell.isEmpty())
        {
            return false;
        }
    }
    return true;
}

Sudoku::Difficulty GameScreen::difficultyToEnum(const QString &difficulty)
{
    if (difficulty == "FACILE")
        return Sudoku::Difficulty::EASY;
    if (difficulty == "MOYEN")
        return Sudoku::Difficulty::MEDIUM;
    if (difficulty == "DIFFICILE")
        return Sudoku::Difficulty::HARD;
    if (difficulty == "EXPERT")
        return Sudoku::Difficulty::EXPERT;
    return Sudoku::Difficulty::EASY;
}

void GameScreen::updateCellStyle(QLabel *cell, int index)
{
    cell->setStyleSheet(Styles::SUDOKU_CELL);

    // Forcer le rafraîchissement du style
    cell->style()->unpolish(cell);
    cell->style()->polish(cell);
}

void GameScreen::resetGame(const QString &difficulty)
{
    // Arrêter le timer avant tout
    if (m_timer)
    {
        m_timer->stop();
    }

    // Désélectionner la cellule actuelle si elle existe
    if (m_selectedCell)
    {
        highlightRelatedCells(m_selectedCell, false);
        m_selectedCell->setProperty("selected", false);
        m_selectedCell = nullptr;
    }

    // Réinitialiser les variables de jeu
    m_difficulty = difficulty;
    m_score = 0;
    m_errorCount = 0;
    m_elapsedSeconds = 0;

    // Générer une nouvelle grille avant de mettre à jour l'interface
    m_grid = Sudoku::generateGrid(difficultyToEnum(difficulty));

    // Mettre à jour les labels
    m_difficultyLabel->setText(QString("NIVEAU: %1").arg(difficulty));
    m_scoreLabel->setText("0");
    m_errorLabel->setText("0/3");
    m_timeLabel->setText("00:00");

    // Réinitialiser et mettre à jour toutes les cellules
    for (size_t i = 0; i < m_cells.size(); ++i)
    {
        QLabel *cell = m_cells[i];
        const Cell &gridCell = m_grid[i];

        // Réinitialiser les propriétés
        cell->setProperty("selected", false);
        cell->setProperty("related", false);
        cell->setProperty("initial", gridCell.isInitial());

        // Mettre à jour le texte
        if (gridCell.isEmpty())
        {
            cell->setText("");
        }
        else
        {
            cell->setText(QString::number(gridCell.value()));
        }

        // Mettre à jour le style
        updateCellStyle(cell, i);
    }

    // Mettre à jour l'état des boutons après avoir généré la nouvelle grille
    updateNumberButtonStates();

    // Redémarrer le timer
    if (m_timer)
    {
        m_timer->start(1000);
    }
}

void GameScreen::updateScore(int points)
{
    m_score += points;
    if (m_score < 0)
        m_score = 0;
    m_scoreLabel->setText(QString::number(m_score));
}

int GameScreen::calculateTimeMultiplier() const
{
    // Le multiplicateur commence à 100% et diminue de 5% toutes les 30 secondes
    int timeMultiplier = 100 - (m_elapsedSeconds / TIME_PENALTY_INTERVAL) * 5;
    return std::max(timeMultiplier, 20); // Minimum 20% des points
}

bool GameScreen::isLineComplete(int row) const
{
    for (int col = 0; col < 9; ++col)
    {
        if (m_grid[Sudoku::getIndex(row, col)].isEmpty())
            return false;
    }
    return true;
}

bool GameScreen::isColumnComplete(int col) const
{
    for (int row = 0; row < 9; ++row)
    {
        if (m_grid[Sudoku::getIndex(row, col)].isEmpty())
            return false;
    }
    return true;
}

bool GameScreen::isBlockComplete(int blockIndex) const
{
    int startRow = (blockIndex / 3) * 3;
    int startCol = (blockIndex % 3) * 3;

    for (int row = startRow; row < startRow + 3; ++row)
    {
        for (int col = startCol; col < startCol + 3; ++col)
        {
            if (m_grid[Sudoku::getIndex(row, col)].isEmpty())
                return false;
        }
    }
    return true;
}

void GameScreen::checkCompletions(int row, int col)
{
    int timeMultiplier = calculateTimeMultiplier();

    // Vérifier la ligne
    if (isLineComplete(row))
    {
        int bonus = LINE_COMPLETION_BONUS * timeMultiplier / 100;
        updateScore(bonus);
    }

    // Vérifier la colonne
    if (isColumnComplete(col))
    {
        int bonus = COLUMN_COMPLETION_BONUS * timeMultiplier / 100;
        updateScore(bonus);
    }

    // Vérifier le bloc
    int blockIndex = (row / 3) * 3 + (col / 3);
    if (isBlockComplete(blockIndex))
    {
        int bonus = BLOCK_COMPLETION_BONUS * timeMultiplier / 100;
        updateScore(bonus);
    }
}

int GameScreen::countNumberInGrid(int number) const
{
    int count = 0;
    for (const auto &cell : m_grid)
    {
        if (cell.value() == number)
            count++;
    }
    return count;
}

void GameScreen::updateNumberButtonStates()
{
    for (QPushButton *button : m_numberButtons)
    {
        int number = button->property("number").toInt();
        bool isAvailable = countNumberInGrid(number) < 9;

        button->setEnabled(isAvailable);
        if (!isAvailable)
        {
            button->setStyleSheet(Styles::NUMBER_BUTTON_DISABLED);
        }
        else
        {
            button->setStyleSheet(Styles::NUMBER_BUTTON);
        }
    }
}

void GameScreen::createVictoryAnimation()
{
    if (m_victoryAnimationGroup)
    {
        delete m_victoryAnimationGroup;
    }

    m_victoryAnimationGroup = new QParallelAnimationGroup(this);

    // Calculer le centre de la grille
    QPointF center(m_gridLayout->geometry().center());

    // Créer une animation pour chaque cellule
    for (QLabel *cell : m_cells)
    {
        QSequentialAnimationGroup *cellAnimation = new QSequentialAnimationGroup(m_victoryAnimationGroup);
        QGraphicsOpacityEffect *opacityEffect = qobject_cast<QGraphicsOpacityEffect *>(cell->graphicsEffect());

        if (!opacityEffect)
        {
            opacityEffect = new QGraphicsOpacityEffect(cell);
            cell->setGraphicsEffect(opacityEffect);
        }

        // Animation de pause avant de commencer
        QPropertyAnimation *pauseAnimation = new QPropertyAnimation(opacityEffect, "opacity");
        QPointF cellPos = cell->mapToParent(cell->rect().center());
        qreal distance = QLineF(cellPos, center).length();
        pauseAnimation->setDuration(distance * DISTANCE_MULTIPLIER);

        pauseAnimation->setStartValue(1.0);
        pauseAnimation->setEndValue(1.0);

        QPropertyAnimation *fadeOut = new QPropertyAnimation(opacityEffect, "opacity");
        fadeOut->setDuration(FADE_ANIMATION_DURATION);
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);

        QPropertyAnimation *fadeIn = new QPropertyAnimation(opacityEffect, "opacity");
        fadeIn->setDuration(FADE_ANIMATION_DURATION);
        fadeIn->setStartValue(0.0);
        fadeIn->setEndValue(1.0);

        // Ajouter les animations dans l'ordre
        cellAnimation->addAnimation(pauseAnimation);
        cellAnimation->addAnimation(fadeOut);
        cellAnimation->addAnimation(fadeIn);

        m_victoryAnimationGroup->addAnimation(cellAnimation);
    }

    connect(m_victoryAnimationGroup, &QParallelAnimationGroup::finished,
            this, &GameScreen::onVictoryAnimationFinished);
}

void GameScreen::startVictoryAnimation()
{
    m_isAnimating = true;
    createVictoryAnimation();
    m_victoryAnimationGroup->start();
}

void GameScreen::onVictoryAnimationFinished()
{
    m_isAnimating = false;
    emit gameOver(true, m_score, m_elapsedSeconds);
}