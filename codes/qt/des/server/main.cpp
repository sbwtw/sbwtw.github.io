
#include "serverwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ServerWindow sw;
    sw.show();

    return app.exec();
}

