#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(420, 400);  // Set the fixed size of the window (200x200 pixels
    w.show();
    w.setWindowTitle("Converter MP3");
    w.setWindowIcon(QIcon(":R:/QT projects/ImgConverter_MP3Player/icon.png"));
    return a.exec();
}
