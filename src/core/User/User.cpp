#include "User.h"

User::User(QObject *parent) : QObject(parent){
    userSex = true;
    userBodyWeight = 0.0;
    userHeight = 0.0;
    userAge = 0;

    goal = 0;
}