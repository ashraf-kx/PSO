#include "mainwindow.h"
#include <QApplication>

#include <time.h>
#include "pso.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    srand(QDateTime::currentDateTime().toTime_t());
    PSO *mPSO = new PSO();

    MainWindow w;
    w.DrawData(mPSO->xData,mPSO->yData);
    w.displayStatics(mPSO->executionTime,mPSO->mGlobalBest.cost);
    w.show();

    return a.exec();
}
