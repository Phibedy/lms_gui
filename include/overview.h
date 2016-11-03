#ifndef LMS_GUI_OVERVIEW
#define LMS_GUI_OVERVIEW

#include <QtWidgets>
#include <lms/logging/event.h>

class DataCollector;
class Overview:public QWidget{
    Q_OBJECT
public:
    Overview(DataCollector *data);
    DataCollector *data;
    void removeClients();
    void addClient(std::string peer, std::int32_t fd);
    void logMessage(lms::logging::Level lvl, std::string tag, std::string text,lms::Time stamp);
    void removeProcesses();
    void addProcess(std::int32_t pid,std::string configfile);
private:
    void createClientList();
    void createConsole();
    void createProfilingOverview();
    void createRuntimeList();

    //overview boxes
    QGroupBox *clientListBox;
    QGroupBox *consoleBox;
    QGroupBox *profilingBox;
    QGroupBox *runtimeListBox;
    QTableWidget* runtimeTable;
    QTableWidget* clientTable;
    QPlainTextEdit* consoleOutput;
};
#endif //LMS_GUI_OVERVIEW
