#include "homescreen.h"
#include "../styles/styles.h"
#include <QFont>
#include <QLabel>

HomeScreen::HomeScreen(QWidget *parent)
    : Screen(parent)
{
    // Ajouter un espace en haut
    m_layout->addSpacing(50);

    // Logo ou icône (à remplacer par votre propre image)
    QLabel *logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":/images/sudoku-logo.png").scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(logoLabel);

    // Titre
    m_titleLabel = new QLabel("SUDOKU", this);
    QFont titleFont("Arial", 48, QFont::Bold);
    m_titleLabel->setFont(titleFont);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet(Styles::TITLE_STYLE);
    m_layout->addWidget(m_titleLabel);

    // Sous-titre
    QLabel *subtitleLabel = new QLabel("Exercez votre esprit logique", this);
    subtitleLabel->setFont(QFont("Arial", 16));
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("color: #2487C7; margin-bottom: 40px;");
    m_layout->addWidget(subtitleLabel);

    // Ajouter un espace
    m_layout->addStretch();

    // Bouton Commencer
    m_startButton = new QPushButton("COMMENCER", this);
    m_startButton->setFont(QFont("Arial", 16, QFont::Bold));
    m_startButton->setStyleSheet(Styles::PRIMARY_BUTTON);
    m_layout->addWidget(m_startButton, 0, Qt::AlignCenter);

    // Ajouter un espace en bas
    m_layout->addStretch();

    // Version
    QLabel *versionLabel = new QLabel("v1.0.0", this);
    versionLabel->setAlignment(Qt::AlignCenter);
    versionLabel->setStyleSheet("color: #2487C7; margin: 20px;");
    m_layout->addWidget(versionLabel);

    // Connecter le signal du bouton
    connect(m_startButton, &QPushButton::clicked, this, &HomeScreen::startClicked);
}