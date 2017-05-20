#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QFileDialog>
#include <QDebug>
#include <QImage>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    size = 50; // to define the size of the pixel block that will be pixelizing rendered
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

    // I work with my teammate Meldrick Reimmer

    pimg = new QImage(filePath);

    ui->FilePathLabel->setText(filePath);

    pixmap = new QPixmap (filePath);

    //pimg = pixmap->toImage();




    // get the label size
    int w, h;
    w=ui->displayLabel->width();
    h=ui->displayLabel->height();

    // with scale preserved
    ui->displayLabel->setPixmap(pixmap->scaled(w,h, Qt :: KeepAspectRatio));
}



// My teacher provide me help for this save button
void MainWindow::on_Save_clicked()
{

    pimg->save("newimage3.png");


}


void MainWindow::on_Pixelized_clicked()
{
    // My classmate Khoi Pham help me for this part of the code about the pixelization

    for(int i = 0; i < pimg->width(); i += size)
        for(int j = 0; j < pimg->height(); j += size){

            int r=0,g=0,b=0,a=0;

            // loop through every pixels of the pixel cube
            for(int k = 0; k < size; ++k)
                for(int l = 0; l < size; ++l){

                    // stopping criterion in case the last cube
                    // that compute data out of image boundary
                    if (i+k < pimg->width() && j+l <pimg->height()) {

                        // convert the QRgb to QColor for color extracting process
                        QColor color(pimg->pixel(i+k,j+l));

                        // extract color channels using QColor built-in functions
                        r += color.red();
                        g += color.green();
                        b += color.blue();
                        a += color.alpha();


                    }
                }

            // calculate mean color value of every channels
            r /= size*size; g /= size*size; b /= size*size; a /= size*size;

            // combine 4 channels into QRgb data type
            QRgb meanColor = qRgba(r,g,b,a);

            // replace the pixel of the cube by the new color (the same loop above)
            for(int k = 0; k < size; ++k)
                for(int l = 0; l < size; ++l)

                    // same stopping criterion as above
                    if (i+k < pimg->width() && j+l <pimg->height())
                        pimg->setPixel(i+k, j+l, meanColor);

        }

    //creation of the pixelizedLabel new label to display the result of the pixelization
    //get the label size
    int w,h;
    w=ui->pixelizedLabel->width();
    h=ui->pixelizedLabel->height();
    QPixmap pixel = QPixmap::fromImage(*pimg); // I use *pimg to dereference my pointer to not overread or overwrite the same image

    // with scale preserved
    ui->pixelizedLabel->setPixmap(pixel.scaled(w,h, Qt::KeepAspectRatio));

}


