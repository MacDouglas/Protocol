#include "cusplot.h"
#include "switcher.h"
#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cusplot w;
    w.show();

//    Dialog dg;
//    dg.show();

    return a.exec();
}
