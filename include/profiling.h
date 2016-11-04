#ifndef LMS_GUI_PROFILING
#define LMS_GUI_PROFILING

#include <QtWidgets>
#include <QChart>
#include <QChartView>
#include <QSplineSeries>

class Profiling:public QWidget{
    Q_OBJECT
public:
    Profiling();
    QTableWidget *traceTable;
    void clearTrace();
    void addTrace(QString name, int mean, int stdev, int min, int max);
private:

    QtCharts::QChart *timeChart;
};
#endif //LMS_GUI_OVERVIEW
