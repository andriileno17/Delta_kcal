#include "User.h"

User::User(QObject *parent) : QObject(parent){
    userName = "";
    userSex = true;
    userBodyWeight = 0.0;
    userHeight = 0.0;
    userAge = 0;

    goal = 0;
}

void User::setUserName(QString inputUserName){
    userName = inputUserName;
}

void User::setSex(bool inputSex){
    userSex = inputSex;
}

void User::setBodyWeight(double inputBodyWeight){
    userBodyWeight = inputBodyWeight;
}

void User::setHeight(double inputHeight){
    userHeight = inputHeight;
}

void User::setAge(int inputAge){
    userAge = inputAge;
}

void User::setActivityCoefficient(double inputActivityCoefficient){
    userActivityCoefficient = inputActivityCoefficient;
}

void User::setGoal(int inputGoal){
    goal = inputGoal;
}

QString User::getUserName() const{
    return userName;
}

bool User::getSex() const{
    return userSex;
}

double User::getBodyWeight() const{
    return userBodyWeight;
}

double User::getHeight() const{
    return userHeight;
}

int User::getAge() const{
    return userAge;
}

double User::getActivityCoefficient() const{
    return userActivityCoefficient;
}

int User::getGoal() const{
    return goal;
}