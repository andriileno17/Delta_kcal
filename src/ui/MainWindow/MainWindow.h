#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "StartScreen.h"
#include "Profile.h"
#include "UserSelectionScreen.h"
#include "UsersPage.h"
#include "MetabolicCore.h"
#include "User.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    MetabolicCore core;
    User currentUser;

    QStackedWidget *stackedWidget;
    StartScreen *startScreen;
    Profile *profileScreen;
    UserSelectionScreen *selectionScreen;
    UsersPage *usersPage;

private slots:
    void goToProfileForm();
    void goToSelectionScreen();
    void goBackToStart();
    void loadSelectedUserToProfile(int userId);
    void goToUsersPage();
};

#endif