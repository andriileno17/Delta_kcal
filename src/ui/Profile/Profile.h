#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QDebug>
#include "MetabolicCore.h"
#include "User.h"

class Profile: public QWidget{
    Q_OBJECT
    public:
        explicit Profile(QWidget *parent = nullptr);

    private slots:
        void onButtonClicked();

    private:
        MetabolicCore core;
        User currentUser;

        QSpinBox *ageBox;
        QDoubleSpinBox *weightBox;
        QDoubleSpinBox *heightBox;
        QComboBox *activityBox;
        QComboBox *goalBox;
        QComboBox *sexBox;
        QPushButton *button;

        QFormLayout *profileLayout;
};

#endif