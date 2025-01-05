#include "difficultyscreen.h"
#include "../styles/styles.h"
#include <QLabel>
#include <QPushButton>
#include <QFont>

DifficultyScreen::DifficultyScreen(QWidget *parent)
    : Screen(parent)
{
    // Ajouter un espace en haut
    m_layout->addSpacing(40);

    // Titre
    QLabel *difficultyTitle = new QLabel("NIVEAU DE DIFFICULTÉ", this);
    QFont titleFont("Arial", 28, QFont::Bold);
    difficultyTitle->setFont(titleFont);
    difficultyTitle->setAlignment(Qt::AlignCenter);
    difficultyTitle->setStyleSheet(Styles::TITLE_STYLE);
    m_layout->addWidget(difficultyTitle);

    // Sous-titre
    QLabel *subtitle = new QLabel("Choisissez votre défi", this);
    subtitle->setFont(QFont("Arial", 16));
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color: #2487C7; margin-bottom: 40px;");
    m_layout->addWidget(subtitle);

    m_layout->addSpacing(30);

    // Structure des niveaux avec leurs descriptions
    struct DifficultyLevel
    {
        QString name;
        QString description;
    };

    QVector<DifficultyLevel> levels = {
        {"FACILE", "Parfait pour débuter"},
        {"MOYEN", "Pour les joueurs réguliers"},
        {"DIFFICILE", "Un vrai défi"},
        {"EXPERT", "Pour les maîtres du Sudoku"}};

    // Boutons de difficulté
    for (int i = 0; i < levels.size(); ++i)
    {
        QWidget *container = new QWidget(this);
        QVBoxLayout *buttonLayout = new QVBoxLayout(container);

        QPushButton *button = new QPushButton(levels[i].name, this);
        button->setFont(QFont("Arial", 14, QFont::Bold));
        button->setStyleSheet(Styles::DIFFICULTY_BUTTON);
        button->setMinimumSize(250, 60);

        QLabel *description = new QLabel(levels[i].description, this);
        description->setAlignment(Qt::AlignCenter);
        description->setStyleSheet("color: #2487C7;");

        buttonLayout->addWidget(button);
        buttonLayout->addWidget(description);
        buttonLayout->setSpacing(5);

        m_layout->addWidget(container, 0, Qt::AlignCenter);

        connect(button, &QPushButton::clicked, this, [this, i]()
                { emit difficultySelected(i); });
    }

    m_layout->addStretch();
}