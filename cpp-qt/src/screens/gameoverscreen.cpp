#include "gameoverscreen.h"
#include "../styles/styles.h"
#include <QFont>
#include <QVBoxLayout>

GameOverScreen::GameOverScreen(bool isWin, int score, int time, QWidget *parent)
    : Screen(parent)
{
    m_layout->addSpacing(50);

    // Titre
    m_titleLabel = new QLabel(isWin ? "VICTOIRE !" : "PERDU !", this);
    QFont titleFont("Arial", 48, QFont::Bold);
    m_titleLabel->setFont(titleFont);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet(isWin ? "color: #9EC33A;" : "color: red;");
    m_layout->addWidget(m_titleLabel);

    m_layout->addSpacing(30);

    // Score
    QLabel *scoreLabel = new QLabel(QString("Score: %1").arg(score), this);
    scoreLabel->setFont(QFont("Arial", 24));
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("color: #2487C7;");
    m_layout->addWidget(scoreLabel);

    // Temps
    int minutes = time / 60;
    int seconds = time % 60;
    QLabel *timeLabel = new QLabel(QString("Temps: %1:%2")
                                       .arg(minutes, 2, 10, QChar('0'))
                                       .arg(seconds, 2, 10, QChar('0')),
                                   this);
    timeLabel->setFont(QFont("Arial", 24));
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setStyleSheet("color: #2487C7;");
    m_layout->addWidget(timeLabel);

    m_layout->addSpacing(50);

    // Bouton Nouvelle Partie
    m_newGameButton = new QPushButton("NOUVELLE PARTIE", this);
    m_newGameButton->setFont(QFont("Arial", 16, QFont::Bold));
    m_newGameButton->setStyleSheet(Styles::PRIMARY_BUTTON);
    m_layout->addWidget(m_newGameButton, 0, Qt::AlignCenter);

    connect(m_newGameButton, &QPushButton::clicked, this, &GameOverScreen::newGameClicked);

    m_layout->addStretch();
}

void GameOverScreen::updateStats(bool isWin, int score, int time)
{
    // Mettre à jour le titre
    m_titleLabel->setText(isWin ? "VICTOIRE !" : "PERDU !");
    m_titleLabel->setStyleSheet(isWin ? "color: #9EC33A;" : "color: red;");

    // Mettre à jour le score
    for (QLabel *label : findChildren<QLabel *>())
    {
        if (label != m_titleLabel)
        {
            if (label->text().startsWith("Score:"))
            {
                label->setText(QString("Score: %1").arg(score));
            }
            else if (label->text().startsWith("Temps:"))
            {
                int minutes = time / 60;
                int seconds = time % 60;
                label->setText(QString("Temps: %1:%2")
                                   .arg(minutes, 2, 10, QChar('0'))
                                   .arg(seconds, 2, 10, QChar('0')));
            }
        }
    }
}