#include "qt_visulation.h"

bool QtVisulation::initialize() {
    mainWindow = new MainWindow();
    mainWindow->show();
    return true;
}

bool QtVisulation::deinitialize() {
    mainWindow->close();
    return true;
}

bool QtVisulation::cycle() {
    my_cycleCounter++;
    mainWindow->updateGui();
    return true;
}
