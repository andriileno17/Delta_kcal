#include "DataBaseManager.h"

DataBaseManager::DataBaseManager(){}

DataBaseManager::~DataBaseManager(){}

bool DataBaseManager::setupDataBase(){
    
    QSqlDatabase db;
    if(QSqlDatabase::contains(QSqlDatabase::defaultConnection)){
        db = QSqlDatabase::database();
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("delta_user.db");
    }
    
    if(!db.open()){
        qDebug() << "Помилка бази даних: " << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    bool success = query.exec("CREATE TABLE IF NOT EXISTS user_profile ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "name TEXT, "
                              "sex BOOLEAN, "
                              "age INTEGER, "
                              "height REAL, "
                              "weight REAL, "
                              "activity REAL, "
                              "goal INTEGER)");

    if (success) qDebug() << "База даних успішно налаштована!";
    return success;
}

QString DataBaseManager::saveUser(const User& user) {
    if (!setupDataBase()) return "Помилка: база не відкрилась";

    QSqlQuery query;
    query.prepare("INSERT INTO user_profile "
                  "(name, sex, age, height, weight, activity, goal) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");

    query.addBindValue(user.getUserName());
    query.addBindValue(user.getSex());
    query.addBindValue(user.getAge());
    query.addBindValue(user.getHeight());
    query.addBindValue(user.getBodyWeight());
    query.addBindValue(user.getActivityCoefficient());
    query.addBindValue(user.getGoal());

    if (query.exec()) {
        return "OK";
    } else {
        return query.lastError().text(); 
    }
}

bool DataBaseManager::loadUser(User& user, int userId) {
    if (!setupDataBase()) return false;

    QSqlQuery query;
    query.prepare("SELECT * FROM user_profile WHERE id = :id");
    query.bindValue(":id", userId);
    
    if (query.exec() && query.next()) {
        user.setUserName(query.value("name").toString());
        user.setSex(query.value("sex").toBool());
        user.setAge(query.value("age").toInt());
        user.setHeight(query.value("height").toDouble());
        user.setBodyWeight(query.value("weight").toDouble());
        user.setActivityCoefficient(query.value("activity").toDouble());
        user.setGoal(query.value("goal").toInt());

        qDebug() << "Користувач завантажений з БД!";
        return true;
    }
    return false;
}

QMap<int, QString> DataBaseManager::getAllUsers() {
    QMap<int, QString> users;
    
    if (!setupDataBase()) {
        users.insert(-1, "ПОМИЛКА: База не відкрилась");
        return users;
    }

    QSqlQuery query;
    if (!query.exec("SELECT id, name FROM user_profile")) {
        users.insert(-1, "ПОМИЛКА SQL: " + query.lastError().text());
        return users;
    }

    while (query.next()) {
        users.insert(query.value("id").toInt(), query.value("name").toString());
    }
    
    return users;
}