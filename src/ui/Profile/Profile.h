#ifndef PROFILE_H
#define PROFILE_H

#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include "MetabolicCore.h"
#include "User.h"
#include "DataBaseManager.h"

class Profile: public QWidget{
    Q_OBJECT
    public:
        explicit Profile(QWidget *parent = nullptr);
        void loadUserFromDB(int userId);
        void saveUser();

        MetabolicCore& getCore();

        int getCurrentUserId();

    signals:
        void backRequested();
        void usersPageRequested();

    private:
        MetabolicCore core;
        User currentUser;
        DataBaseManager dbManager;

        QFormLayout *profileLayout;

        QLineEdit *nameBox;
        QSpinBox *ageBox;
        QDoubleSpinBox *weightBox;
        QDoubleSpinBox *heightBox;
        QComboBox *activityBox;
        QComboBox *goalBox;
        QComboBox *sexBox;

        QPushButton *calculateButton;
        QPushButton *backButton;

        void loadDataToUi();
};

#endif