#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QStyle>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_actionMp3_File_triggered();
    void on_actionPhotos_triggered();

private:
    Ui::MainWindow *ui;

    QMediaPlayer *MPlayer;
    QAudioOutput *audioOutput;
};
#endif // MAINWINDOW_H
