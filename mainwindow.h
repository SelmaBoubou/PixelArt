#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Load_clicked();

    void on_Save_clicked();


    void on_Pixelized_clicked();



public:
    int n;
private:

    Ui::MainWindow *ui;
    QImage *pimg; //pointer to my image
    QPixmap *pixmap;
    int size;




};

#endif // MAINWINDOW_H
