#ifndef METABOLICCORE_H
#define METABOLICCORE_H

#include <QObject>
#include <QString>

class MetabolicCore: public QObject{
    Q_OBJECT
    public:
        explicit MetabolicCore(QObject *parent = nullptr);
        ~MetabolicCore();

        void countBMR(QString userSex, double userBodyweight, double userHeight, int userAge);
        void countTDEE(int BMR, int activityCoefficient);
        void countDelta(int TDEE, QString goal);

        void countMacros(int delta, int userBodyWeight, double activityCoefficient);

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