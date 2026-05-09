#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "StartScreen.h"
#include "Profile.h"
#include "UserSelectionScreen.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stackedWidget;
    StartScreen *startScreen;
    Profile *profileScreen;
    UserSelectionScreen *selectionScreen;

private slots:
    void goToProfileForm();
    void goToSelectionScreen();
    void goBackToStart();
    void loadSelectedUserToProfile(int userId);
};

#endif