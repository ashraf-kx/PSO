#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
       // this->setWindowIcon(QIcon(":/Icons/IconAOCR.png"));
    this->setWindowTitle("PSO V 0.0.3");
}

void MainWindow::DrawData(QVector<double> VectorX,QVector<double> VectorY){
    x = VectorX;
    y = VectorY;
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("iteration");
    ui->customPlot->yAxis->setLabel("cost globale");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0,1000);
    ui->customPlot->yAxis->setRange(-1400000,-300000);
    ui->customPlot->replot();
}

void MainWindow::displayStatics(uint executionTime,double cost){
    ui->statusBar->showMessage("Time : "+QString::number(executionTime)+" s.              Cost : "+QString::number(cost),100000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
