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

    bool m_running;
public:
    DataCollector(MainWindow *window);

    bool running(){
        return m_running;
    }
    void readMessages();
    void receivedPackage();
    void parsePackages();

    bool hasGraph(){
        return false;
    }

    QString getGraphImagePath(){
        return "";
    }

};


#endif //LMS_GUI_DATA_COLLECTOR_H
