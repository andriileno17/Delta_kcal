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
#include "DataBaseManager.h"
#include "StatisticsPage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    MetabolicCore core;
    User currentUser;
    DataBaseManager *dbManager;

    QStackedWidget *stackedWidget;
    StartScreen *startScreen;
    Profile *profileScreen;
    UserSelectionScreen *selectionScreen;
    UsersPage *usersPage;
    StatisticsPage *statisticsPage;

private slots:
    void goToProfileForm();
    void goToSelectionScreen();
    void goBackToStart();
    void loadSelectedUser(int userId);
    void goToUsersPage();
    void goToStatisticsPage();
    void returnToUsersPage();
};

#endif