#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->resize(400, 500);

    stackedWidget = new QStackedWidget(this);

    startScreen = new StartScreen(this);
    profileScreen = new Profile(this);
    selectionScreen = new UserSelectionScreen(this);
    usersPage = new UsersPage(this);
    statisticsPage = new StatisticsPage(this);

    stackedWidget->addWidget(startScreen);
    stackedWidget->addWidget(profileScreen);
    stackedWidget->addWidget(selectionScreen);
    stackedWidget->addWidget(usersPage);
    stackedWidget->addWidget(statisticsPage);

    setCentralWidget(stackedWidget);

    connect(startScreen, &StartScreen::createNewUserRequested, this, &MainWindow::goToProfileForm);
    connect(startScreen, &StartScreen::loadUserRequested, this, &MainWindow::goToSelectionScreen);
    connect(selectionScreen, &UserSelectionScreen::backRequested, this, &MainWindow::goBackToStart);
    connect(profileScreen, &Profile::backRequested, this, &MainWindow::goBackToStart);
    connect(selectionScreen, &UserSelectionScreen::userSelected, this, &MainWindow::loadSelectedUser);
    connect(profileScreen, &Profile::usersPageRequested, this, &MainWindow::goToUsersPage);
    connect(usersPage, &UsersPage::backRequested, this, &MainWindow::goToSelectionScreen);
    connect(usersPage, &UsersPage::statisticsRequested, this, &MainWindow::goToStatisticsPage);
    connect(statisticsPage, &StatisticsPage::backRequested, this, &MainWindow::returnToUsersPage);
}

void MainWindow::goToProfileForm() {
    stackedWidget->setCurrentWidget(profileScreen);
}

void MainWindow::goToSelectionScreen() {
    selectionScreen->updateList();
    stackedWidget->setCurrentWidget(selectionScreen);
}

void MainWindow::loadSelectedUser(int userId){
    profileScreen->loadUserFromDB(userId);

    int k = 0, p = 0, f = 0, c = 0;
    QDate today = QDate::currentDate();

    dbManager->loadDailyLog(userId, today, k, p, f, c);

    usersPage->setActiveUserId(userId);
    usersPage->loadEatenData(k, p, f, c);
    usersPage->updateCharts(profileScreen->getCore());

    stackedWidget->setCurrentWidget(usersPage);
}

void MainWindow::goBackToStart() {
    stackedWidget->setCurrentWidget(startScreen);
}

void MainWindow::goToUsersPage(){
    profileScreen->saveUser();
    usersPage->updateCharts(profileScreen->getCore());
    usersPage->setActiveUserId(profileScreen->getCurrentUserId());
    stackedWidget->setCurrentWidget(usersPage);
}

void MainWindow::goToStatisticsPage(){
    statisticsPage->loadStatistics(profileScreen->getCurrentUserId(), dbManager);
    stackedWidget->setCurrentWidget(statisticsPage);
}

void MainWindow::returnToUsersPage(){
    stackedWidget->setCurrentWidget(usersPage);
}