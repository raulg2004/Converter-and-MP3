#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QFileInfo>
#include <QImage>
#include <QMediaPlayer>
#include <QUrl>
#include <QAudioOutput>
#include <QPdfWriter>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)  // Call the constructor of the base class QMainWindow
    , ui(new Ui::MainWindow)  // Initialize the UI pointer
{
    ui->setupUi(this);  // Setup the user interface from the .ui file

    // Initialize the media player and audio output
    MPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    MPlayer->setAudioOutput(audioOutput);  // Connect media player to audio output

    // Set icons for play and pause buttons
    ui->pushButton_3->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_4->setIcon(style()->standardIcon(QStyle::SP_MediaPause));

    // Connect the slider value change to the volume control slot
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::on_horizontalSlider_valueChanged);
}

MainWindow::~MainWindow()
{
    delete ui;           // Clean up the UI
    delete audioOutput;  // Clean up the audio output
}

void MainWindow::on_pushButton_clicked()
{
    // Open a file dialog to browse for an image file
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files(*.png *.jpg *.jpeg *.bmp *.pdf *.avif)");
    ui->lineEdit->setText(fileName);  // Set the selected file name to the line edit
}

void MainWindow::on_actionPhotos_triggered()
{
    // Open a file dialog to browse for an image file (similar to on_pushButton_clicked)
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files(*.png *.jpg *.jpeg *.bmp *.pdf *.avif)");
    ui->lineEdit->setText(fileName);  // Set the selected file name to the line edit
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = ui->lineEdit->text();  // Get the file name from the line edit

    if (!fileName.isEmpty()) {  // Check if a file name is selected
        QFileInfo fileinfo(fileName);
        QString newFilename = fileinfo.path() + "/" + fileinfo.completeBaseName();  // Create a base for the new file name

        QImage image(fileName);  // Load the image
        if (!image.isNull()) {  // Check if the image is valid
            int format = ui->comboBox->currentIndex();  // Get the selected format from the combo box
            switch (format) {
            case 0:
                newFilename += ".png";
                break;
            case 1:
                newFilename += ".jpg";
                break;
            case 2:
                newFilename += ".jpeg";
                break;
            case 3:
                newFilename += ".bmp";
                break;
            case 4:
                newFilename += ".pdf";
                break;
            default:
                break;
            }

            qDebug() << newFilename << format;  // Debug output for the new file name and format

            if (format == 4) { // PDF conversion
                QPdfWriter writer(newFilename);
                writer.setPageSize(QPageSize(image.size()));
                QPainter painter(&writer);
                painter.drawImage(0, 0, image);
                painter.end();

                QMessageBox::information(this, "Success", "The Image was Converted to PDF");
            } else {
                if (image.save(newFilename, 0, -1)) {  // Save the image in the new format
                    QMessageBox::information(this, "Success", "The Image was Converted");  // Show success message
                } else {
                    QMessageBox::warning(this, "Failed", "The Image was NOT Converted");  // Show failure message
                }
            }
        } else {
            QMessageBox::warning(this, "Failed", "Failed To Open Image");  // Show error message if the image couldn't be opened
        }
    } else {
        QMessageBox::warning(this, "Failed", "No File is Selected");  // Show error message if no file is selected
    }
}

void MainWindow::on_actionMp3_File_triggered()
{
    // Open a file dialog to browse for an MP3 file
    QString FileName = QFileDialog::getOpenFileName(this, "Open MP3", "", "MP3 Files(*.mp3)");
    if (!FileName.isEmpty()) {  // Check if a file name is selected
        MPlayer->setSource(QUrl::fromLocalFile(FileName));  // Set the media player source to the selected file
        ui->label_2->setText(QFileInfo(FileName).fileName());  // Set the label to show the file name
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    MPlayer->play();  // Play the selected MP3 file
}

void MainWindow::on_pushButton_4_clicked()
{
    MPlayer->pause();  // Pause the MP3 file
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);  // Adjust the volume based on the slider value
}
