#ifndef DAILYLOG_H
#define DAILYLOG_H

#include <QDate>
#include <QString>

class DailyLog{
    public:
        DailyLog();
        bool loadDailyLog();

        int getLogId() const;
        int getUserId() const;
        QDate getDate() const;
        int getKcal() const;
        int getProtein() const;
        int getFat() const;
        int getCarbs() const;
        double getWeight() const;

        void setLogId(int id);
        void setUserId(int id);
        void setDate(const QDate& d);
        void setKcal(int k);
        void setProtein(int p);
        void setFat(int f);
        void setCarbs(int c);
        void setWeight(int w);
        
        void addNutrients(int k, int p, int f, int c);

    private:
        int logId;
        int userId;
        QDate date;
        int kcal;
        int protein;
        int fat;
        int carbs;
        double weight;
};

#endif