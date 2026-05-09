#include "StartScreen.h"

StartScreen::StartScreen(QWidget *parent) : QWidget(parent) {
    newUserButton = new QPushButton("Додати користувача", this);
    loadUserFromDBButton = new QPushButton("Завантажити існуючого користувача", this);

    layout = new QVBoxLayout(this);
    layout->addWidget(newUserButton);
    layout->addWidget(loadUserFromDBButton);
    this->setLayout(layout);

    connect(newUserButton, &QPushButton::clicked, this, &StartScreen::createNewUserRequested);
    connect(loadUserFromDBButton, &QPushButton::clicked, this, &StartScreen::loadUserRequested);
}