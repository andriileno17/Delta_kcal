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
    bool success1 = query.exec("CREATE TABLE IF NOT EXISTS user_profile ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name TEXT, "
                "sex BOOLEAN, "
                "age INTEGER, "
                "height REAL, "
                "weight REAL, "
                "activity REAL, "
                "goal INTEGER)");

    bool success2 = query.exec("CREATE TABLE IF NOT EXISTS daily_logs ("
               "log_id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER, "
               "log_date TEXT, "
               "kcal INTEGER, "
               "protein INTEGER, "
               "fat INTEGER, "
               "carbs INTEGER, "
               "weight REAL, "
               "FOREIGN KEY(user_id) REFERENCES user_profile(id) ON DELETE CASCADE, "
               "UNIQUE(user_id, log_date)"
               ")");

    return success1 && success2;
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

bool DataBaseManager::loadDailyLog(int userId, const QDate& date, int& kcal, int& protein, int& fat, int& carbs){
    if(!setupDataBase()) return false;

    QSqlQuery query;
    query.prepare("SELECT kcal, protein, fat, carbs FROM daily_logs WHERE user_id = :uid AND log_date = :date");
    query.bindValue(":uid", userId);
    query.bindValue(":date", date);

    if(query.exec() && query.next()){
        kcal = query.value("kcal").toInt();
        protein = query.value("protein").toInt();
        fat = query.value("fat").toInt();
        carbs = query.value("carbs").toInt();

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

void DataBaseManager::addMealToLog(int userId, const QDate& date, int kcal, int protein, int fat, int carbs){
    QSqlQuery query;
    QString dateString = date.toString("yyyy-MM-dd");

    query.prepare("SELECT log_id, kcal, protein, fat, carbs FROM daily_logs WHERE user_id = :userId AND log_date = :logDate");
    query.bindValue(":userId", userId);
    query.bindValue(":logDate", dateString);

    if(query.exec() && query.next()){
        int existingKcal = query.value("kcal").toInt();
        int existingProtein = query.value("protein").toInt();
        int existingFat = query.value("fat").toInt();
        int existingCarbs = query.value("carbs").toInt();
        
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE daily_logs SET kcal = :k, protein = :p, fat = :f, carbs = :c WHERE user_id = :userId AND log_date = :logDate");
        updateQuery.bindValue(":k", existingKcal + kcal);
        updateQuery.bindValue(":p", existingProtein + protein);
        updateQuery.bindValue(":f", existingFat + fat);
        updateQuery.bindValue(":c", existingCarbs + carbs);
        updateQuery.bindValue(":userId", userId);
        updateQuery.bindValue(":logDate", dateString);
        updateQuery.exec();
    } else {
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO daily_logs (user_id, log_date, kcal, protein, fat, carbs) "
                            "VALUES (:userId, :logDate, :k, :p, :f, :c)");
        insertQuery.bindValue(":userId", userId);
        insertQuery.bindValue(":logDate", dateString);
        insertQuery.bindValue(":k", kcal);
        insertQuery.bindValue(":p", protein);
        insertQuery.bindValue(":f", fat);
        insertQuery.bindValue(":c", carbs);
        insertQuery.exec();
    }
}

bool DataBaseManager::updateUserWeight(int userId, double newWeight){
    if(!setupDataBase()) return false;

    QSqlQuery q1;
    q1.prepare("UPDATE user_profile SET weight = :w WHERE id = :uid");
    q1.bindValue(":w", newWeight);
    q1.bindValue(":uid", userId);
    q1.exec();

    QSqlQuery q2;
    q2.prepare("UPDATE daily_logs SET weight = :w WHERE user_id = :uid AND log_date = :date");
    q2.bindValue(":w", newWeight);
    q2.bindValue(":uid", userId);
    q2.bindValue(":date", QDate::currentDate().toString("yyyy-MM-dd"));
    q2.exec();

    return true;
}

QList<DailyLog> DataBaseManager::getMonthlyHistory(int userId){
    QList<DailyLog> history;
    if(!setupDataBase()) return history;

    QSqlQuery query;
    query.prepare("SELECT log_date, kcal, protein, fat, carbs, weight FROM daily_logs "
                  "WHERE user_id = :uid ORDER BY log_date DESC LIMIT 30");
    query.bindValue(":uid", userId);

    if (query.exec()) {
        while (query.next()) {
            DailyLog log;
            log.setDate(QDate::fromString(query.value("log_date").toString(), "yyyy-MM-dd"));
            log.setKcal(query.value("kcal").toInt());
            log.setProtein(query.value("protein").toInt());
            log.setFat(query.value("fat").toInt());
            log.setCarbs(query.value("carbs").toInt());
            log.setWeight(query.value("weight").toDouble());
            
            history.prepend(log); 
        }
    }
    return history;
}

