#include "qt_visulation.h"
#include <iostream>

int main(int argc,char *argv[]){

    QApplication* app = new QApplication(argc, argv);
    QtVisulation gui;
    gui.initialize();
    while (true){
        app->processEvents();
        gui.cycle();
    }
    gui.deinitialize();
    return(0);
}
