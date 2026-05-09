#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User: public QObject{
    Q_OBJECT
    public:
        explicit User(QObject *parent = nullptr);

        void setUserName(QString inputUserName);
        void setSex(bool inputSex);
        void setBodyWeight(double inputBodyWeight);
        void setHeight(double inputHeight);
        void setAge(int inputAge);
        void setActivityCoefficient(double inputActivityCoefficient);
        void setGoal(int inputGoal);

        QString getUserName() const;
        bool getSex() const;
        double getBodyWeight() const;
        double getHeight() const;
        int getAge() const;
        double getActivityCoefficient() const;
        int getGoal() const;

    private:
        int userId;
        QString userName;

        bool userSex;
        double userBodyWeight;
        double userHeight;
        int userAge;
        double userActivityCoefficient;
        int goal;
};

#endif