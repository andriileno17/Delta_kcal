#ifndef USER_H
#define USER_H

#include <QObject>

class User: public QObject{
    Q_OBJECT
    public:
        explicit User(QObject *parent = nullptr);

        void setSex(bool inputSex);
        void setBodyWeight(double inputBodyWeight);
        void setHeight(double inputHeight);
        void setAge(int inputAge);
        void setActivityCoefficient(double inputActivityCoefficient);
        void setGoal(int inputGoal);

        bool getSex() const;
        double getBodyWeight() const;
        double getHeight() const;
        int getAge() const;
        double getActivityCoefficient() const;
        int getGoal() const;

    private:
        int userId;

        bool userSex;
        double userBodyWeight;
        double userHeight;
        int userAge;
        double userActivityCoefficient;
        int goal;
};

#endif