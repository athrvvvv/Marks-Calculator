#include "mainwindow.h"
#include "version_check.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    prompt_version_update::version_update();
    return a.exec();
}
