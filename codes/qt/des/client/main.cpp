
#include "clientwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ClientWindow cw;
    cw.show();

    return app.exec();
}
