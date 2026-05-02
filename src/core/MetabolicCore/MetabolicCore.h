#ifndef METABOLICCORE_H
#define METABOLICCORE_H

#include <QObject>
#include <QString>

class MetabolicCore: public QObject{
    Q_OBJECT
    public:
        explicit MetabolicCore(QObject *parent = nullptr);
        ~MetabolicCore();

        void countBMR(bool userSex, double userBodyweight, double userHeight, int userAge);
        void countTDEE(double activityCoefficient);
        void countDelta(int goal);
        void countMacros(int userBodyWeight, double activityCoefficient);

        void calculateNorm(bool userSex, double userBodyWeight, double userHeight, int userAge, double activityCoefficient, int goal);

    private:
        double activityCoefficient;

        int BMR;
        int TDEE;
        int delta;

        int protein;
        int fat;
        int carbs;
};

#endif