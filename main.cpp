#include "getstudent.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GetStudent w;
    w.show();

    return a.exec();
}
