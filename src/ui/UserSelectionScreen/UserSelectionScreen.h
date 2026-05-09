#ifndef USERSELECTIONSCREEN_H
#define USERSELECTIONSCREEN_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "DataBaseManager.h"

class UserSelectionScreen: public QWidget{
    Q_OBJECT
    public:
        explicit UserSelectionScreen(QWidget *parent = nullptr);
        void updateList();

    signals:
        void userSelected(int userId);
        void backRequested();

    private slots:
        void onSelectClicked();

    private:
        QListWidget *userList;
        QPushButton *selectButton;
        QPushButton *backButton;
        DataBaseManager dbManager;
};

#endif