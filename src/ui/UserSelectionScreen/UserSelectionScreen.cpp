#include "UserSelectionScreen.h"
#include <QMessageBox>
#include <QDebug>

UserSelectionScreen::UserSelectionScreen(QWidget *parent) : QWidget(parent) {
    userList = new QListWidget(this);
    selectButton = new QPushButton("Вибрати", this);
    backButton = new QPushButton("Назад", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(userList);
    layout->addWidget(selectButton);
    layout->addWidget(backButton);
    this->setLayout(layout);

    connect(selectButton, &QPushButton::clicked, this, &UserSelectionScreen::onSelectClicked);
    connect(backButton, &QPushButton::clicked, this, [this](){ emit backRequested(); });
}

void UserSelectionScreen::updateList() {
    userList->clear(); 
    
    QMap<int, QString> users = dbManager.getAllUsers();
    
    for (auto it = users.begin(); it != users.end(); ++it) {
        QString name = it.value();
        
        if (name.trimmed().isEmpty()) {
            name = "Без імені (ID: " + QString::number(it.key()) + ")";
        }
        
        QListWidgetItem *item = new QListWidgetItem(name, userList);
        
        item->setForeground(Qt::black);
        
        item->setData(Qt::UserRole, it.key()); 
    }
}

void UserSelectionScreen::onSelectClicked() {
    QListWidgetItem *selectedItem = userList->currentItem(); 
    
    if (selectedItem) {
        int userId = selectedItem->data(Qt::UserRole).toInt(); 
        emit userSelected(userId); 
    } else {
        QMessageBox::warning(this, "Увага", "Будь ласка, виберіть користувача зі списку.");
    }
}