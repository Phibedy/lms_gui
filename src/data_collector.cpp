#include <data_collector.h>
#include <thread>
#include <main_window.h>
#include <lms/logging/event.h>
#include <exception>
#include <unistd.h>

DataCollector::DataCollector():m_connected(false),m_broadcast(false){}

void DataCollector::connectToMaster(){
    //check if we were already connected
    m_broadcast = false;
    if(m_connected){
        m_connected = false;
        m_thread.join();
        m_client.sock().close();
    }
    try{
        std::cout<<"trying to open /tmp/lms.sock"<<std::endl;
        m_client.connectUnix("/tmp/lms.sock");
        std::cout<<"opened"<<std::endl;
    }catch(std::exception e){
        std::cout<<"could not open it: "<<e.what()<<std::endl;
        usleep(1000000); //TODO needed to be able to open the file if the master server is started afterwards?
        return;
    }
    m_connected = true;
    //start thread to listen to msgs
    m_thread = std::thread([this](){
        while(m_connected){
            lms::Response res;
            lms::ProtobufSocket::Error resType;
            try{
                resType = m_client.sock().readMessage(res);
            }catch(std::exception e){
                std::cout<<"readMessage failed: "<<e.what()<<std::endl;
                continue;
            }
            if(resType == lms::ProtobufSocket::OK){
                std::lock_guard<std::mutex> myLock(resposeMutex);
                responseBuffer.push_back(res);
            }else if(resType == lms::ProtobufSocket::ERROR){
                std::cout<<"could not read message: "<<"ERROR"<<std::endl;
                //m_running=false;
                usleep(5000);
            }else if(resType == lms::ProtobufSocket::CLOSED){
                std::cout<<"could not read message: "<<"Connection closed!"<<std::endl;
                m_connected = false;
                usleep(5000);
            }else{
                std::cout<<"could not read message: "<<"UNKOWN"<<std::endl;
                usleep(5000);
            }
        }
    });
}
void DataCollector::attachRuntime(std::string pid){
    m_pid = pid; //TODO clear it if we disconnect
    lms::Request req;
    lms::Request_Attach* att = req.mutable_attach();
    att->set_id(pid);

    if(m_client.sock().writeMessage(req) != lms::ProtobufSocket::OK){
        m_broadcast = false;
        m_pid = "";
    }
}
void DataCollector::refresh(){
    if(m_pid.length() == 0)
        return;
    //ask for profiling
    lms::Request req;
    auto prof = req.mutable_profiling();
    prof->set_id(m_pid);
    if(m_client.sock().writeMessage(req) != lms::ProtobufSocket::OK){
        //TODO error handling
    }

}

void DataCollector::cycle(){
    if(!connected()){
        return;
    }
    //ask for runtimes every time after time
    if(!m_broadcast){
        try{
            m_broadcast = true;
            lms::Request req;
            req.mutable_listen_broadcasts();
            if(m_client.sock().writeMessage(req) != lms::ProtobufSocket::OK){
                std::cout<<"mutable_listen_broadcasts failed"<<std::endl;
                m_broadcast = false;
            }
            //ask for all data once
            req.mutable_list_clients();
            if(m_client.sock().writeMessage(req) != lms::ProtobufSocket::OK){
                std::cout<<"mutable_list_clients failed"<<std::endl;
                m_broadcast = false;
            }
            req.mutable_list_processes();
            if(m_client.sock().writeMessage(req) != lms::ProtobufSocket::OK){
                std::cout<<"mutable_list_processes failed"<<std::endl;
                m_broadcast = false;
            }
        }catch(std::exception e){
            m_broadcast = false;
            std::cout<<"writeMessage failed" <<e.what()<<std::endl;
            return;
        }
    }
    //TODO
    refresh();
    parsePackages();
}

void DataCollector::parsePackages(){
    std::lock_guard<std::mutex> myLock(resposeMutex);
    if(responseBuffer.size() == 0)
        return;
    //std::cout<<"parsePackage: msgcount: "<<responseBuffer.size()<<std::endl;
    for(const lms::Response &res:responseBuffer){
        //std::cout<<"msg-content: "<<res.content_case()<<std::endl;
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
            //std::cout<<"Inforpackage: "<<std::to_string(res.info().pid()) << ", version "<<std::to_string(res.info().version());
            break;
        case lms::Response::kLogEvent:
        {
            lms::logging::Level lvl;
            lms::Time time;
            //TODO

            mainWindow->overview->logMessage(lvl, res.log_event().tag(),res.log_event().text(),time);
            mainWindow->logging->addMsg(QString::fromStdString(res.log_event().tag()),QString::fromStdString(res.log_event().text()),lvl,time);
        }
            break;
        case lms::Response::kModuleList:

            break;
        case lms::Response::kProcessList:
        {
            //std::cout<<"got processList: "<<res.process_list().processes_size()<<std::endl;
            mainWindow->overview->removeProcesses();
            for(int i = 0; i <res.process_list().processes_size(); i++){
                mainWindow->overview->addProcess(res.process_list().processes(i).pid(),res.process_list().processes(i).config_file());
            }
        }
            break;
        case lms::Response::kProfilingSummary:
        {
            mainWindow->profiling->clearTrace();
            for(int i = 0; i< res.profiling_summary().traces_size(); i++){
                const ::lms::Response::ProfilingSummary::Trace& sum = res.profiling_summary().traces(i);
                mainWindow->profiling->addTrace(QString::fromStdString(sum.name()),sum.avg(),sum.std(),sum.min(),sum.max());
            }
        }
            break;
        default:
            break;
        }
    }
    responseBuffer.clear();
}
