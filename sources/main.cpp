#include "../include/mainwindow.h"
#include <QApplication>
#include <QWindow>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    a.setWindowIcon(QIcon(":/foto.ico"));
    window.setFixedSize(1150,550);
    window.show();
    return a.exec();
}
