#include "MetabolicCore.h"

MetabolicCore::MetabolicCore(QObject *parent) :QObject(parent){
    activityCoefficient = 0.0;

    BMR = 0;
    TDEE = 0;
    delta = 0;

    protein = 0;
    fat = 0;
    carbs = 0;
}

MetabolicCore::~MetabolicCore(){}

MetabolicCore::countBMR(bool userSex, double userBodyWeight, double userHeight, int userAge){
    if(userSex == true){
        BMR = 10 * userBodyWeight + 6.25 * userHeight + 5 * userAge + 5;
    } else if (userSex = false){
        BMR = 10 * userBodyWeight + 6.25 * userHeight + 5 * userAge - 161;
    }
}

MetabolicCore::countTDEE(double activityCoefficient){
    TDEE = BMR * activityCoefficient;
}

MetabolicCore::countDelta(int goal){
    if(goal < 0){
        delta = TDEE - TDEE * 0.15;
    } else if (goal > 0){
        delta = TDEE + TDEE * 0.15;
    } else if (goal == 0){
        delta = TDEE;
    }
}

MetabolicCore::countMacros(int userBodyWeight, double activityCoefficient){
    double proteinPerKg = 1.0;
    
    if (activityCoefficient <= 1.2) {
        proteinPerKg = 1.2;
    } else if (activityCoefficient <= 1.375) {
        proteinPerKg = 1.5;
    } else if (activityCoefficient <= 1.55) {
        proteinPerKg = 1.7;
    } else if (activityCoefficient <= 1.725) {
        proteinPerKg = 2.0;
    } else {
        proteinPerKg = 2.2;
    }

    protein = userBodyWeight * proteinPerKg;

    fat = userBodyWeight * 1.0; 
    
    carbs = (delta - (protein * 4) - (fat * 9)) / 4;
}

MetabolicCore::calculateNorm(bool userSex, double userBodyWeight, double userHeight, int userAge, double activityCoefficient, int goal){
    countBMR(userSex, userBodyWeight, userHeight, userAge);
    countTDEE(activityCoefficient);
    countDelta(goal);
    countMacros(userBodyWeight, activityCoefficient);
}