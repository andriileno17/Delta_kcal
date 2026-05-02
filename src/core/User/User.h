#ifndef USER_H
#define USER_H

#include <QObject>

class User: public QObject{
    Q_OBJECT
    public:
        explicit User(QObject *parent = nullptr);

    private:
        int userId;

        bool userSex;
        double userBodyWeight;
        double userHeight;
        int userAge;

        int goal;
};

#endif