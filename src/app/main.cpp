#include "mainwindow.h"
#include <QApplication>
#include <QThreadPool>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NuweTimer::App::MainWindow w;
    w.show();
    a.exec();

    QThreadPool::globalInstance()->waitForDone(10000);
    return 0;
}
