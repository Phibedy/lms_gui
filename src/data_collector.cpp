#include <data_collector.h>
#include <messages.pb.h>


DataCollector::DataCollector(){
    m_client = connectToMasterServer();
}

lms::Client DataCollector::connectToMasterServer(){
    //TODO check if file is available
    return lms::Client::fromUnix("/tmp/lms.sock");
}

void DataCollector::readMessages(){
    lms::Response res;
    m_client.sock().readMessage(res);
    switch (res.content_case()) {
    case lms::Response::kClientList:
        res.client_list().clients_size();
        res.client_list().clients(0);
        break;
    case lms::Response::kInfo:
        res.info().pid();
        res.info().version();
        break;
    case lms::Response::kLogEvent:

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



void DataCollector::receivedPackage(){

}
