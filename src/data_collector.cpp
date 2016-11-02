#include <data_collector.h>
#include <thread>
#include <main_window.h>
#include <lms/logging/event.h>
#include <exception>

DataCollector::DataCollector(MainWindow *window):m_running(false){
    //start the read thread
    mainWindow = window;
}

void DataCollector::readMessages(){
    if(!running()){
        try{
            m_client.connectUnix("/tmp/lms.sock");
        }catch(std::exception e){
            return;
        }
    }
    m_running = true;
    m_thread = std::thread([this](){
        while(m_running){
            lms::Response res;
            if(m_client.sock().readMessage(res)){
                std::lock_guard<std::mutex> myLock(resposeMutex);
                responseBuffer.push_back(res);
            }else{
                m_running = false;
            }

        }
    });
}

void DataCollector::parsePackages(){
    if(!running()){
        return;
    }
    std::lock_guard<std::mutex> myLock(resposeMutex);
    for(const lms::Response &res:responseBuffer){
        switch (res.content_case()) {
        case lms::Response::kClientList:
        {
            mainWindow->overview->removeClients();
            for(int i = 0; i <  res.client_list().clients_size(); i++){
                mainWindow->overview->addClient(res.client_list().clients(0).peer(),res.client_list().clients(0).fd());
            }
        }
            break;
        case lms::Response::kInfo:
            res.info().pid();
            res.info().version();
            break;
        case lms::Response::kLogEvent:
        {
            lms::logging::Level lvl;
            lms::Time time;
            //TODO

            mainWindow->overview->logMessage(lvl, res.log_event().tag(),res.log_event().text(),time);
        }
            break;
        case lms::Response::kModuleList:

            break;
        case lms::Response::kProcessList:

            break;
        case lms::Response::kProfilingSummary:

            break;
        default:
            break;
        }
    }
}



void DataCollector::receivedPackage(){

}
