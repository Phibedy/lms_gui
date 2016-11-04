#ifndef LMS_GUI_DATA_COLLECTOR_H
#define LMS_GUI_DATA_COLLECTOR_H
#include <QString>
#include <lms/client.h>
#include <messages.pb.h>
#include <mutex>
#include <thread>

class MainWindow;



class DataCollector{
    MainWindow* mainWindow;
    lms::Client m_client;
    std::mutex resposeMutex;
    std::vector<lms::Response> responseBuffer;
    std::thread m_thread;

    std::string m_pid;
    bool m_connected;
    bool m_broadcast;
    void parsePackages();

public:
    DataCollector();

    void setMainWindow(MainWindow *window){
        this->mainWindow = window;
    }

    void cycle();
    void connectToMaster();
    void attachRuntime(std::string pid);

    void refresh();

    bool connected(){
        return m_connected;
    }
    bool hasGraph(){
        return false;
    }

    QString getGraphImagePath(){
        return "";
    }

};


#endif //LMS_GUI_DATA_COLLECTOR_H
