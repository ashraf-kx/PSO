#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void DrawData(QVector<double> VectorX,QVector<double> VectorY);
    ~MainWindow();

    void displayStatics(uint executionTime, double cost);
private:
    Ui::MainWindow *ui;
    QVector<double> x, y;
};

#endif // MAINWINDOW_H
