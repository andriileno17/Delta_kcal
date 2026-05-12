#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->resize(400, 500);

    stackedWidget = new QStackedWidget(this);

    startScreen = new StartScreen(this);
    profileScreen = new Profile(this);
    selectionScreen = new UserSelectionScreen(this);
    usersPage = new UsersPage(this);

    stackedWidget->addWidget(startScreen);
    stackedWidget->addWidget(profileScreen);
    stackedWidget->addWidget(selectionScreen);
    stackedWidget->addWidget(usersPage);

    setCentralWidget(stackedWidget);

    connect(startScreen, &StartScreen::createNewUserRequested, this, &MainWindow::goToProfileForm);
    connect(startScreen, &StartScreen::loadUserRequested, this, &MainWindow::goToSelectionScreen);
    connect(selectionScreen, &UserSelectionScreen::backRequested, this, &MainWindow::goBackToStart);
    connect(profileScreen, &Profile::backRequested, this, &MainWindow::goBackToStart);
    connect(selectionScreen, &UserSelectionScreen::userSelected, this, &MainWindow::loadSelectedUserToProfile);
    connect(profileScreen, &Profile::usersPageRequested, this, &MainWindow::goToUsersPage);
}

void MainWindow::goToProfileForm() {
    stackedWidget->setCurrentWidget(profileScreen);
}

void MainWindow::goToSelectionScreen() {
    selectionScreen->updateList();
    stackedWidget->setCurrentWidget(selectionScreen);
}

void MainWindow::goBackToStart() {
    stackedWidget->setCurrentWidget(startScreen);
}

void MainWindow::loadSelectedUserToProfile(int userId) {
    profileScreen->loadUserFromDB(userId);
    stackedWidget->setCurrentWidget(profileScreen);
}

void MainWindow::goToUsersPage(){
    profileScreen->saveUser();
    usersPage->updateCharts(profileScreen->getCore());
    stackedWidget->setCurrentWidget(usersPage);
}