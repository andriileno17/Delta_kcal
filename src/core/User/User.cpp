#include "User.h"

User::User(QObject *parent) : QObject(parent){
    userBodyWeight = 0.0;
    userHeight = 0.0;
    userAge = 0;

    goal = "";
    isSportsmen = false; 
}