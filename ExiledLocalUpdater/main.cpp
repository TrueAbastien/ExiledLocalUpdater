#include "Application.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w;
    w.show();

    int result =  a.exec();
    w.Cleanup();
    return result;
}
