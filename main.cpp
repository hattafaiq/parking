#include "utama.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    utama w;
    w.show();
    return a.exec();
}
