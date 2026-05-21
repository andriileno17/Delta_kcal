#include "DailyLog.h"

DailyLog::DailyLog(){}

int DailyLog::getLogId() const{
    return logId;
}

int DailyLog::getUserId() const{
    return userId;
}

QDate DailyLog::getDate() const{
    return date;
}

int DailyLog::getKcal() const{
    return kcal;
}

int DailyLog::getProtein() const{
    return protein;
}

int DailyLog::getFat() const{
    return fat;
}

int DailyLog::getCarbs() const{
    return carbs;
}

double DailyLog::getWeight() const{
    return weight;
}

void DailyLog::setLogId(int id){
    logId = id;
}

void DailyLog::setUserId(int id){
    userId = id;
}

void DailyLog::setDate(const QDate& d){
    date = d;
}

void DailyLog::addNutrients(int k, int p, int f, int c){
    kcal += k;
    protein += p;
    fat += f;
    carbs += c;
}

void DailyLog::setKcal(int k){
    kcal = k;
}

void DailyLog::setProtein(int p){
    protein = p;
}

void DailyLog::setFat(int f){
    fat = f;
}

void DailyLog::setCarbs(int c){
    carbs = c;
}

void DailyLog::setWeight(int w){
    weight = w;
}