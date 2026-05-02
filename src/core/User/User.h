#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User: public QObject{
    Q_OBJECT
    public:
        explicit User(QObject *parent = nullptr);

    private:
        int userId;

        QString userSex;
        double userBodyWeight;
        double userHeight;
        int userAge;

        QString goal;
        bool isSportsmen;


};

#endif