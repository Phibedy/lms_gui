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


class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow();


private:

    //profiling boxes
    QGroupBox* profilePage;
    void createProfilingPage();

};

#endif // QT_VISULATION_MAIN_WINDOW_H
