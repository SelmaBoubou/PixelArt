#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QPainter>
#include <QGraphicsView>
#include <QImage>
#include <QBuffer>
#include <QFile>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    n=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Load_clicked()
{
    QString filePath = QFileDialog :: getOpenFileName(
                this,
                "Open a file",
                QString(),
                "Images (*.gif *.jpig *.jpg)");

    // I use the code of my team mate Meldrick Reimmer
    pimg = new QImage(filePath);

    ui->FilePathLabel->setText(filePath);

    QPixmap pixmap (filePath);

    // get the label size
    int w, h;
    w=ui->displayLabel->width();
    h=ui->displayLabel->height();

    // with scale preserved
    ui->displayLabel->setPixmap(pixmap.scaled(w,h, Qt :: KeepAspectRatio));
}

// source: http://stackoverflow.com/questions/16362191/qt-grab-widget-and-save-image
void MainWindow::on_Save_clicked()
{
//   QString imagePath = QFileDialog :: getSaveFileName(
//                this,
//                "Save as",
//                "Choose a filename",
//                "Images (*.gif *.jpig *.jpg *.png)");


//    ui->SavePathLabel->setText(imagePath);
//    QPixmap pixmap (imagePath);
    pimg->save("");





}
