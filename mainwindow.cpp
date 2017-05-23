#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QFileDialog>
#include <QImage>
#include <QDir>
#include <QColor>




using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //initialisation of my pointers
    pixelizedimage = new QImage;
    pimg = new QImage;
    finalimage = new QImage;


}

MainWindow::~MainWindow()
{
    // delete my pointers
    delete pixelizedimage;
    delete pimg;
   delete finalimage;
    delete ui;
}

void MainWindow::on_Load_clicked()
{
    QString filePath = QFileDialog :: getOpenFileName(
                this,
                "Open a file",
                QString(),
                "Images (*.png *.jpig *.jpg)");//to open images in any formats.

    // I work with my teammate Meldrick Reimmer

    pimg = new QImage(filePath);

    ui->FilePathLabel->setText(filePath);



    // get the label size
    int w, h;
    w=ui->displayLabel->width();
    h=ui->displayLabel->height();

    // with scale preserved
    ui->displayLabel->setPixmap(QPixmap::fromImage(pimg->scaled(w,h, Qt :: KeepAspectRatio)));
}



// My teacher provide me help for this save button I improve it to be able to save anywhere I want.
void MainWindow::on_Save_clicked()
{
    QString savePath = QFileDialog :: getSaveFileName(
                this,
                "Save a file",
                QString(),
                "Images (*.gif *.jpig *.jpg)");

    ui->SavePathLabel->setText(savePath);

    finalimage->save(savePath);




}


void MainWindow::on_Pixelized_clicked()
{

    pixelizedimage = new QImage (pimg->scaled(valueimagesize,valueimagesize,Qt::KeepAspectRatio));
    // ui->pixelizedLabel->setText(pixelizedimage);

    // get the label size
    int w, h;
    w=ui->displayLabel->width();
    h=ui->displayLabel->height();

    // with scale preserved
    ui->pixelizedLabel->setPixmap(QPixmap::fromImage(pixelizedimage->scaled(w,h, Qt::KeepAspectRatio)));

}



void MainWindow::on_LoadMultiple_clicked()
{

    // StackOverflow, User : Apin, Date : Mar 15 2016
    // explanation : Here we will load all the image that we want to store into te database
    QString adressPath = QFileDialog::getExistingDirectory(this, tr("Select DB folder"));
    QDir dir(adressPath);
    QStringList filter;
    filter << QLatin1String("*.png");
    filter << QLatin1String("*.jpeg");
    filter << QLatin1String("*.jpg");
    dir.setNameFilters(filter);
    QFileInfoList filelistinfo = dir.entryInfoList();
    QStringList fileList;
    // END OF SOURCE

    // Go through every file

    foreach (const QFileInfo& fileinfo, filelistinfo) {
        QString imageFile = fileinfo.absoluteFilePath(); // variable which contain the path of the current image
        //imageFile is the image path, just put your load image code here

        // My classemate Antoine Merlet provide me help for this part

        QImage img(imageFile); // creation of a temporary image available only in this part of the code.

        img = img.scaled( valuepixelsize, valuepixelsize, Qt::KeepAspectRatio); // creation of the pixelized image
        QImage *newimage = new QImage(img); // creation of a pointer of the new image
        resolutiondatabase.push_back(newimage); // store into the database

    }

}

QColor* MainWindow::mean(QImage *img){ // pointer to my image which return a pointer to QColor
    // I use my classemate Antoine Merlet code for this part.

    // get image size
    int h = img->height();
    int w = img->width();

    // initilalization of the RGB
    int sumR = 0;
    int sumG = 0;
    int sumB = 0;

    // Going through the image
    for ( int i = 0; i < w; i++){
        for ( int j = 0; j < h; j++){

            // get the pixel value
            QColor pixelvalue( img->pixel( i, j));


            sumR += pixelvalue.red();
            sumG += pixelvalue.green();
            sumB += pixelvalue.blue();
        }
    }
    // compute the mean.
    sumR /= h * w;
    sumG /= h * w;
    sumB /= h * w;

    // creating the resulting color as a QRgb
    return new QColor( sumR, sumG, sumB);
}


QImage* MainWindow::optimizationpixels(const QColor& colorofpixel)
{

    // Explanation: In this part we have to find the best image corresponding to each pixels. Using the function mean above.

    // Counters for RGB and Total
    int differenceR, differenceG, differenceB, differenceT;

    // goal is the value to achieve for the best optimization
    int goal = 255 * 3;
    // we choose 255 cause the value of a pixel is between 0 and 255 and we multiplie by 3 cause 3 channels for the RGB

    // The image which obtain the best result in term of matching with the pixels
    QImage* matchingimage;

    // iterator which choose the image in the database
    for (std::vector<QImage*>::iterator it = resolutiondatabase.begin(); it != resolutiondatabase.end() ; it++) {

        // Actual image
        QImage* actualImage = *it;
        QColor* actualMean = mean(actualImage);

        // Compute the absolute mean difference
        differenceR = abs(colorofpixel.red() -  actualMean->red()); // absolute difference value of the given pixels and the mean of the pixels
        differenceG = abs(colorofpixel.green() - actualMean->green());
        differenceB = abs(colorofpixel.blue() -  actualMean->blue());

        // Addition of the total absolte difference
        differenceT = differenceR + differenceG + differenceB;

        // Check if new best result
        if (differenceT <= goal) {
            matchingimage = actualImage;

            // Do better than the previous one
            goal = differenceT;
        }
    }
    return matchingimage; // return the image who correspond the most
}

void MainWindow::on_Draw_Pixels_clicked()
{


    // get pixelized image size
    int h = pixelizedimage->height();
    int w = pixelizedimage->width();


    // initialization of the matching image result for a given pixel
    QImage* matchingimageResult ;

    // Prepare the result image with good size
   finalimage = new QImage( w * valuepixelsize, h * valuepixelsize, QImage::Format_RGB32);

    // for every pixel in the pixelizedimage
    for ( int i = 0; i < w; i++){
        for ( int j = 0; j < h; j++){

            // Get the actual pixel
            QColor actualpixel(pixelizedimage->pixel(i,j));

            // Get the best result in the DataBase
            matchingimageResult = optimizationpixels(actualpixel);

            // Take all the pixels of the matching images and put it in the good place on the final image

            // For every pixel in the resolutiondatabase
            for (int k = 0; k< matchingimageResult->width();k++){
                for (int l = 0; l < matchingimageResult->height(); l++){

                    // actual pixel
                    QColor actualMatch =matchingimageResult->pixel(k,l);

                   // copy on the output finalimage the actual pixel above.
                   finalimage->setPixel(i * valuepixelsize + k, j * valuepixelsize + l, actualMatch.rgb());
                }
            }
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(*finalimage)); // display the final image, I dereference my pointer
}

void MainWindow::on_savepixelized_clicked()
{
    QString savePath1 = QFileDialog :: getSaveFileName(
                this,
                "Save a file",
                QString(),
                "Images (*.png *.jpig *.jpg)");

    //ui->SavePathLabel->setText(savePath);

    pixelizedimage->save(savePath1);

}
