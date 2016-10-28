#ifndef LMS_GUI_LOGGING
#define LMS_GUI_LOGGING

#include <QtWidgets>

class Logging:public QWidget{
    Q_OBJECT
public:
    QTableWidget *messageTable;
    QGroupBox *filterBox;
    Logging();
private:
};
#endif //LMS_GUI_OVERVIEW
