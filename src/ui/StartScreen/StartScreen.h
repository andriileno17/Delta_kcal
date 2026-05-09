#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class StartScreen : public QWidget {
    Q_OBJECT
public:
    explicit StartScreen(QWidget *parent = nullptr);

signals:
    void createNewUserRequested();
    void loadUserRequested();

private:
    QPushButton *newUserButton;
    QPushButton *loadUserFromDBButton;
    QVBoxLayout *layout;
};

#endif