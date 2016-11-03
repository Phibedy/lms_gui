#ifndef QT_VISULATION_MAIN_WINDOW_H
#define QT_VISULATION_MAIN_WINDOW_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QSplineSeries>
#include <QValueAxis>
#include <QAction>
#include <QTabWidget>
#include <QGroupBox>
#include "iostream"
#include <overview.h>
#include <logging.h>
#include <profiling.h>
#include <graph.h>

class DataCollector;
class MainWindow : public QMainWindow{
    Q_OBJECT
    QTabWidget* qtab;
public:
    MainWindow(DataCollector *data);
    void updateGui();
    //lazy
    Overview *overview;
    Profiling *profiling;
    Logging *logging;
    Graph *graph;
};

#endif // QT_VISULATION_MAIN_WINDOW_H
