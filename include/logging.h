#ifndef LMS_GUI_LOGGING
#define LMS_GUI_LOGGING

#include <QtWidgets>
#include <lms/logging/event.h>

class Logging:public QWidget{
    Q_OBJECT
public:
    QTableWidget *messageTable;
    QGroupBox *filterBox;
    Logging();
    void filter(const QString &s);
    void addMsg(const QString &tag,const QString &text,const lms::logging::Level &lvl, const lms::Time &stamp);
private:
};
#endif //LMS_GUI_OVERVIEW
