#include "profiling.h"
#include <iostream>

Profiling::Profiling(){
    QVBoxLayout *layout = new QVBoxLayout;
    //show list with all modules name,mean,stdev
    traceTable = new QTableWidget;
    traceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    traceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    traceTable->setSelectionMode(QAbstractItemView::SingleSelection);
    traceTable->verticalHeader()->setVisible(false);
    traceTable->setShowGrid(false);
    traceTable->setRowCount(0);
    traceTable->setColumnCount(5);
    QStringList qlist;
    qlist<<"Name"<<"mean in us"<<"std in us"<<"min in us"<<"max in us";
    traceTable->setHorizontalHeaderLabels(qlist);
    layout->addWidget(traceTable);


    //show plot over time

    timeChart = new QtCharts::QChart();
    QtCharts::QSplineSeries *tmp = new QtCharts::QSplineSeries();
    tmp->append(0,10);
    tmp->append(1,12);
    tmp->append(2,9);
    //timeChart->legend()->hide();
    timeChart->addSeries(tmp);
    tmp->setName("tmp");
    timeChart->setTitle("");
    timeChart->createDefaultAxes();
    timeChart->axisY()->setTitleText("Time");
    //timeChart->axisX()->setVisible(false);
    timeChart->axisX()->setTitleText("Iteration");
    QtCharts::QChartView *chartView = new QtCharts::QChartView(timeChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);
    //TODO set offset timeChart->axisY()->setMax(13);

    setLayout(layout);
}

void Profiling::clearTrace(){
    traceTable->clear();
    traceTable->setRowCount(0);
    QStringList qlist;
    qlist<<"Name"<<"mean in us"<<"std in us"<<"min in us"<<"max in us";
    traceTable->setHorizontalHeaderLabels(qlist);
}

void Profiling::addTrace(QString name, int mean, int stdev, int min, int max){
    traceTable->insertRow(0);
    traceTable->setItem(0, 0, new QTableWidgetItem(name));
    traceTable->setItem(0, 1, new QTableWidgetItem(QString::number(mean)));
    traceTable->setItem(0, 2, new QTableWidgetItem(QString::number(stdev)));
    traceTable->setItem(0, 3, new QTableWidgetItem(QString::number(min)));
    traceTable->setItem(0, 4, new QTableWidgetItem(QString::number(max)));
    QStringList qlist;
    qlist<<"Name"<<"mean in us"<<"std in us"<<"min in us"<<"max in us";
    traceTable->setHorizontalHeaderLabels(qlist);

}
