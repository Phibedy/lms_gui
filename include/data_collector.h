#ifndef LMS_GUI_DATA_COLLECTOR_H
#define LMS_GUI_DATA_COLLECTOR_H
#include <QString>
#include <lms/client.h>
class DataCollector{
    DataCollector();
    static DataCollector* m_instance;
    lms::Client m_client;
public:

    static DataCollector* getInstance(){
        if(m_instance == nullptr){
            m_instance = new DataCollector();
        }
        return m_instance;
    }

    bool connected(){
        return false;
    }

    lms::Client connectToMasterServer();
    void readMessages();
    void receivedPackage();

    bool hasGraph(){
        return false;
    }

    QString getGraphImagePath(){
        return "";
    }

};


#endif //LMS_GUI_DATA_COLLECTOR_H
