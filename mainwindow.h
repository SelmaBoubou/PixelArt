#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QColor* mean(QImage *img);
    QImage* optimizationpixels(const QColor& colorofpixel);
    ~MainWindow();



private slots:
    void on_Load_clicked();

    void on_Save_clicked();

    void on_Pixelized_clicked();

    void on_LoadMultiple_clicked();

    void on_Draw_Pixels_clicked();

    void on_savepixelized_clicked();

private:

    Ui::MainWindow *ui;
    QImage *pixelizedimage;
    QImage *pimg; //pointer to my image
    QImage *finalimage; // my final image
    std::vector<QImage*> resolutiondatabase; // creation of a vector to store all the low resolution of all the images in the database.
    int valueimagesize = 50; // definition of the resolution size of my image
    int valuepixelsize = 10; // definition of the resoltion size of each pixels



};

#endif // MAINWINDOW_H
