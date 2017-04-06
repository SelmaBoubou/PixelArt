#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
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
    // source: http://creative-punch.net/2014/02/opening-displaying-saving-images-qt/


public:
    int n;
private:

    Ui::MainWindow *ui;
    QImage *pimg; //pointer to my image


};

#endif // MAINWINDOW_H