#include "qt_visulation.h"

bool QtVisulation::initialize() {
    mainWindow = new MainWindow();

    dataCollector = new DataCollector(mainWindow);
    mainWindow->show();
    return true;
}

bool QtVisulation::deinitialize() {
    mainWindow->close();
    return true;
}

bool QtVisulation::cycle() {
    my_cycleCounter++;
    dataCollector->cycle();
    mainWindow->updateGui();
    return true;
}
