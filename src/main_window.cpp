#include <QtWidgets>

#include "main_window.h"
#include "overview.h"
#include "profiling.h"
#include "logging.h"
#include <iostream>
#include <functional>
#include <string>

MainWindow::MainWindow(){
    //create gui
    QTabWidget* qtab = new QTabWidget(this);
    setCentralWidget(qtab);
    //Add pages
    QWidget *overview = new Overview();
    qtab->addTab(overview,"Overview");
    QWidget *profiling = new Profiling();
    qtab->addTab(profiling,"Profiling");
    QWidget *logging = new Logging();
    qtab->addTab(logging,"Logging");

    setWindowTitle(tr("LMS GUI"));
}

void MainWindow::createProfilingPage(){
    profilePage = new QGroupBox(tr("Profiling"));
    QGridLayout *layout = new QGridLayout;
    profilePage->setLayout(layout);
}
