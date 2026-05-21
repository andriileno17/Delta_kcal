#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include <QDate>
#include <QList>
#include "User.h"
#include "DailyLog.h"

class DataBaseManager {
    public:
        DataBaseManager();
        ~DataBaseManager();

        bool setupDataBase();
        QString saveUser(const User& user);
        bool loadUser(User& user, int userId);
        bool loadDailyLog(int userId, const QDate& date, int& kcal, int& protein, int& fat, int& carbs);
        QMap<int, QString> getAllUsers();
        QList<DailyLog> getMonthlyHistory(int userId);

        void addMealToLog(int userId, const QDate& date, int kcal, int protein, int fat, int carbs);
        bool updateUserWeight(int userId, double newWeight);
};

#endif