#ifndef METABOLICCORE_H
#define METABOLICCORE_H

#include <QObject>
#include <QString>
#include "User.h"

class MetabolicCore: public QObject{
    Q_OBJECT
    public:
        explicit MetabolicCore(QObject *parent = nullptr);
        ~MetabolicCore();

        void countBMR(User& user);
        void countTDEE(User& user);
        void countDelta(User& user);
        void countMacros(User& user);

        void calculateNorm(User& user);

        int getDelta() const;
        int getProtein() const;
        int getFat() const;
        int getCarbs() const;

        void copyDataFrom(MetabolicCore& other);

    private:
        int BMR;
        int TDEE;
        int delta;

        int protein;
        int fat;
        int carbs;
};

#endif