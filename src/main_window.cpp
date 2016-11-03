#include <QtWidgets>

#include "main_window.h"
#include "overview.h"
#include "profiling.h"
#include "logging.h"
#include "graph.h"
#include <iostream>
#include <functional>
#include <string>
#include <data_collector.h>
MainWindow::MainWindow(DataCollector *data){
    //create gui
    qtab = new QTabWidget(this);
    setCentralWidget(qtab);
    //Add pages
    overview = new Overview(data);
    qtab->addTab(overview,"Overview");
    profiling = new Profiling();
    qtab->addTab(profiling,"Profiling");
    logging = new Logging();
    qtab->addTab(logging,"Logging");
    graph = new Graph();
    qtab->addTab(graph,"Graph");
    setWindowTitle(tr("LMS GUI"));

    //resize it
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

void MainWindow::updateGui(){
    bool attachedToRuntime = true;
    for(int i = 1; i < (int) qtab->children().size(); i++){
        qtab->setTabEnabled(i,attachedToRuntime);
    }

}
