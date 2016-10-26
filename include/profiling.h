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
    QTableWidget *moduleTable;
private:

    QtCharts::QChart *timeChart;
    void setModuleTable(int row,QString name,QString type, int mean, int stdev);
};
#endif //LMS_GUI_OVERVIEW
