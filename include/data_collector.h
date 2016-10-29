#ifndef LMS_GUI_DATA_COLLECTOR_H
#define LMS_GUI_DATA_COLLECTOR_H
#include <QString>
class DataCollector{
    DataCollector();
    static DataCollector* m_instance;
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

    void connectToRuntime(const QString &s){

    }

    void receivedPackage(){

    }

    void hasGraph(){
        return false;
    }

    QString getGraphImagePath(){
        return "";
    }

};


#endif //LMS_GUI_DATA_COLLECTOR_H
