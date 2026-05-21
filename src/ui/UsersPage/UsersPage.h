#ifndef USERSPAGE_H
#define USERSPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QHBoxLayout>
#include <QDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include "DataBaseManager.h"
#include "MetabolicCore.h"
#include "User.h"
#include "Profile.h"

class UsersPage: public QWidget{
    Q_OBJECT
    public:
        explicit UsersPage(QWidget *parent = nullptr);
        void updateCharts(MetabolicCore& updatedCore);

        void setActiveUserId(int id);

        void loadEatenData(int k, int p, int f, int c);

    signals:
        void backRequested();
        void statisticsRequested();

    private slots:
        void onAddMealClicked();
        void onUpdateWeightClicked();

    private:
        DataBaseManager dbManager;
        MetabolicCore core;
        User user;
        Profile *profile;
        DailyLog *currentLog;

        int currentUserId;

        int totalKcal;
        int kcalEaten;

        int totalProtein;
        int proteinEaten;

        int totalFat;
        int fatEaten;

        int totalCarbs;
        int carbsEaten;

        QPushButton *goToStatistics;
        QPushButton *addMeal;
        QPushButton *backButton;
        QPushButton *updateWeight;

        QPieSeries *kcalSeries;
        QChart *kcalChart;
        QChartView *kcalView;

        QPieSeries *proteinSeries;
        QChart *proteinChart;
        QChartView *proteinView;

        QPieSeries *fatSeries;
        QChart *fatChart;
        QChartView *fatView;

        QPieSeries *carbsSeries;
        QChart *carbsChart;
        QChartView *carbsView;

        QVBoxLayout *pageLayout;
        QHBoxLayout *diagramLayout;

        void loadData();
};

#endif