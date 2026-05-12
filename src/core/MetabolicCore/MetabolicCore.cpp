#include "MetabolicCore.h"

MetabolicCore::MetabolicCore(QObject *parent) :QObject(parent){
    BMR = 0;
    TDEE = 0;
    delta = 0;

    protein = 0;
    fat = 0;
    carbs = 0;
}

MetabolicCore::~MetabolicCore(){}

void MetabolicCore::countBMR(User& user){
    if(user.getSex() == true){
        BMR = 10 * user.getBodyWeight() + 6.25 * user.getHeight() - 5 * user.getAge() + 5;
    } else if (user.getSex() == false){
        BMR = 10 * user.getBodyWeight() + 6.25 * user.getHeight() - 5 * user.getAge() - 161;
    }
}

void MetabolicCore::countTDEE(User& user){
    TDEE = BMR * user.getActivityCoefficient();
}

void MetabolicCore::countDelta(User& user){
    if(user.getGoal() < 0){
        delta = TDEE - TDEE * 0.15;
    } else if (user.getGoal() > 0){
        delta = TDEE + TDEE * 0.15;
    } else if (user.getGoal() == 0){
        delta = TDEE;
    }
}

void MetabolicCore::countMacros(User& user){
    double proteinPerKg = 1.0;
    
    if (user.getActivityCoefficient() <= 1.2) {
        proteinPerKg = 1.2;
    } else if (user.getActivityCoefficient() <= 1.375) {
        proteinPerKg = 1.5;
    } else if (user.getActivityCoefficient() <= 1.55) {
        proteinPerKg = 1.7;
    } else if (user.getActivityCoefficient() <= 1.725) {
        proteinPerKg = 2.0;
    } else {
        proteinPerKg = 2.2;
    }

    protein = user.getBodyWeight() * proteinPerKg;

    fat = user.getBodyWeight() * 1.0; 
    
    carbs = (delta - (protein * 4) - (fat * 9)) / 4;
}

void MetabolicCore::calculateNorm(User& user){
    countBMR(user);
    countTDEE(user);
    countDelta(user);
    countMacros(user);
}

int MetabolicCore::getDelta() const{
    return delta;
}

int MetabolicCore::getProtein() const{
    return protein;
}

int MetabolicCore::getFat() const{
    return fat;
}

int MetabolicCore::getCarbs() const{
    return carbs;
}

void MetabolicCore::copyDataFrom(MetabolicCore& other) {
    this->delta = other.getDelta();
    this->protein = other.getProtein();
    this->fat = other.getFat();
    this->carbs = other.getCarbs();
}