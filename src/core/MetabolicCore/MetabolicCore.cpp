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

MetabolicCore::countBMR(QString userSex, double userBodyWeight, double userHeight, int userAge){
    if(userSex == "male"){
        BMR = 10 * userBodyWeight + 6.25 * userHeight + 5 * userAge + 5;
    } else if (userSex = "female"){
        BMR = 10 * userBodyWeight + 6.25 * userHeight + 5 * userAge - 161;
    }
}

MetabolicCore::countTDEE(int BMR, int activityCoefficient){
    TDEE = BMR * activityCoefficient;
}

MetabolicCore::countDelta(int TDEE, QString goal){
    if(goal == "deficit"){
        delta = TDEE - TDEE * 0.15;
    } else if (goal == "proficit"){
        delta = TDEE + TDEE * 0.15;
    } else if (goal == "maintain"){
        delta = TDEE;
    }
}

MetabolicCore::countMacros(int delta, int userBodyWeight, double activityCoefficient){
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