#include "gamestatemanager.h"

GameStateManager &GameStateManager::getInstance()
{
    static GameStateManager instance;
    return instance;
}

GameStateManager::GameStateManager(QObject *parent)
    : QObject(parent), m_currentState(GameState::HOME), m_score(0), m_time(0), m_isWin(false)
{
}

void GameStateManager::startNewGame()
{
    m_currentState = GameState::DIFFICULTY_SELECTION;
    emit stateChanged(m_currentState);
}

void GameStateManager::selectDifficulty(const QString &difficulty)
{
    m_difficulty = difficulty;
    m_currentState = GameState::PLAYING;
    emit stateChanged(m_currentState);
    emit difficultyChanged(difficulty);
}

void GameStateManager::endGame(bool isWin, int score, int time)
{
    m_isWin = isWin;
    m_score = score;
    m_time = time;
    m_currentState = GameState::GAME_OVER;
    emit stateChanged(m_currentState);
    emit gameEnded(isWin, score, time);
}

void GameStateManager::returnToHome()
{
    m_currentState = GameState::HOME;
    emit stateChanged(m_currentState);
}