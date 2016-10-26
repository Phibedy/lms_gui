#include <QtWidgets>

#include "main_window.h"
#include "overview.h"
#include "profiling.h"
#include "logging.h"
#include "graph.h"
#include <iostream>
#include <functional>
#include <string>

MainWindow::MainWindow(){
    //create gui
    qtab = new QTabWidget(this);
    setCentralWidget(qtab);
    //Add pages
    QWidget *overview = new Overview();
    qtab->addTab(overview,"Overview");
    QWidget *profiling = new Profiling();
    qtab->addTab(profiling,"Profiling");
    QWidget *logging = new Logging();
    qtab->addTab(logging,"Logging");
    QWidget *graph = new Graph();
    qtab->addTab(graph,"Graph");
    setWindowTitle(tr("LMS GUI"));

    //resize it
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

void MainWindow::createProfilingPage(){
    profilePage = new QGroupBox(tr("Profiling"));
    QGridLayout *layout = new QGridLayout;
    profilePage->setLayout(layout);
}

void MainWindow::updateGui(){
    bool attachedToRuntime = true;
    for(int i = 1; i < (int) qtab->children().size(); i++){
        qtab->setTabEnabled(i,attachedToRuntime);
    }

}
