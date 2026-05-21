#ifndef STATISTICSPAGE_H
#define STATISTICSPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>
#include "DataBaseManager.h"

class StatisticsPage : public QWidget {
    Q_OBJECT
public:
    explicit StatisticsPage(QWidget *parent = nullptr);
    void loadStatistics(int userId, DataBaseManager* dbManager);

signals:
    void backRequested();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPushButton *backButton;
    QPushButton *btnCalories;
    QPushButton *btnWeight;
    QList<DailyLog> historyData;
    int currentUserId = -1;
    bool showWeightGraph = false;
};

#endif