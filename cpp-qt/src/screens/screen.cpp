#include "screen.h"

Screen::Screen(QWidget *parent)
    : QWidget(parent), m_layout(new QVBoxLayout(this))
{
}