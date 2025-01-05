#ifndef STYLES_H
#define STYLES_H

#include <QString>

namespace Styles
{

    const QString WINDOW_STYLE = R"(
    QMainWindow {
        background-color: #f0f2f5;
    }
)";

    const QString TITLE_STYLE = R"(
    QLabel {
        color: #2c3e50;
        font-family: 'Arial', sans-serif;
        font-weight: bold;
        padding: 20px;
    }
)";

    const QString PRIMARY_BUTTON = R"(
    QPushButton {
        background-color: #3498db;
        color: white;
        border: none;
        border-radius: 25px;
        padding: 15px 32px;
        font-weight: bold;
        min-width: 200px;
        margin: 10px;
    }
    QPushButton:hover {
        background-color: #2980b9;
        transform: scale(1.05);
    }
    QPushButton:pressed {
        background-color: #2472a4;
    }
)";

    const QString DIFFICULTY_BUTTON = R"(
    QPushButton {
        background-color: #2ecc71;
        color: white;
        border: none;
        border-radius: 25px;
        padding: 15px 32px;
        font-weight: bold;
        min-width: 200px;
        margin: 10px;
    }
    QPushButton:hover {
        background-color: #27ae60;
        transform: scale(1.05);
    }
    QPushButton:pressed {
        background-color: #219a52;
    }
)";

    const QString SUDOKU_CELL = R"(
    QLabel {
        background-color: white;
        border: 1px solid #e0e0e0;
    }
    QLabel[initial="true"] {
        color: #2487C7;
        font-weight: bold;
    }
    QLabel[initial="false"] {
        color: #9EC33A;
    }
    QLabel:hover {
        background-color: #f8faf0;
    }
    QLabel[related="true"] {
        background-color: #f5f7f0;
    }
    QLabel[selected="true"] {
        background-color: #e5ef9f;
    }
    )";

    const QString NUMBER_BUTTON = R"(
    QPushButton {
        background-color: #2487C7;
        color: white;
        border: none;
        border-radius: 24px;
        font-weight: bold;
    }
    QPushButton:hover {
        background-color: #1f75b0;
    }
    QPushButton:pressed {
        background-color: #1a6698;
    }
    )";

    const QString NUMBER_BUTTON_DISABLED = R"(
    QPushButton {
        background-color: #cccccc;
        color: #888888;
        border: none;
        border-radius: 24px;
        font-weight: bold;
    }
    QPushButton:hover {
        background-color: #cccccc;
    }
    QPushButton:pressed {
        background-color: #cccccc;
    }
    )";

}

#endif // STYLES_H