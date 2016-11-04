#include "qt_visulation.h"

bool QtVisulation::initialize() {
    dataCollector = new DataCollector();
    mainWindow = new MainWindow(dataCollector);
    dataCollector->setMainWindow(mainWindow);
    mainWindow->show();
    return true;
}

bool QtVisulation::deinitialize() {
    mainWindow->close();
    return true;
}

bool QtVisulation::cycle() {
    my_cycleCounter++;
    if(!dataCollector->connectedToMaster()){
        dataCollector->connectToMaster();
    }
    dataCollector->cycle();
    mainWindow->updateGui();
    return true;
}
