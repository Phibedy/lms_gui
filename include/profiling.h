#ifndef LMS_GUI_PROFILING
#define LMS_GUI_PROFILING

#include <QtWidgets>

class Profiling:public QWidget{
    Q_OBJECT
public:
    Profiling();
    QTableWidget *moduleTable;
private:

    void setModuleTable(int row,QString name,QString type, int mean, int stdev);
};
#endif //LMS_GUI_OVERVIEW
