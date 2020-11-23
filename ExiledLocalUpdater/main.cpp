#include "Application.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w;
    w.show();

    int res = a.exec();
    w.Cleanup();
    return res;
}
