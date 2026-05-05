#include <QApplication>
#include "Profile.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    Profile window;
    window.show();

    return app.exec();
}