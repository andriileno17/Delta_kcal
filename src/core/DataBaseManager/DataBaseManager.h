#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include "User.h"

class DataBaseManager {
public:
    DataBaseManager();
    ~DataBaseManager();

    bool setupDataBase();
    QString saveUser(const User& user);
    bool loadUser(User& user, int userId);
    QMap<int, QString> getAllUsers();
};

#endif