#include <QtWidgets>

#include "main_window.h"
#include <iostream>
#include <functional>
#include <string>

MainWindow::MainWindow(){
    QTabWidget* qtab = new QTabWidget(this);
    setCentralWidget(qtab);
    //create gui

    //Overview page
    createClientList();
    createRuntimeList();
    createConsole();
    createProfilingOverview();
    //add them
    QWidget *overview = new QWidget();
    QVBoxLayout *overviewLayout = new QVBoxLayout;
    overviewLayout->addWidget(clientListBox);
    overviewLayout->addWidget(runtimeListBox);
    overviewLayout->addWidget(consoleBox);
    overview->setLayout(overviewLayout);
    qtab->addTab(overview,"Overview");

    //Profiling page
    createProfilingPage();
    //Create gui
    QWidget *profiling = new QWidget();
    QVBoxLayout *profileLayout = new QVBoxLayout;
    profileLayout->addWidget(profilePage);
    profiling->setLayout(profileLayout);
    qtab->addTab(profiling,"Profile");


    setWindowTitle(tr("LMS GUI"));
}

void MainWindow::createClientList(){
    clientListBox = new QGroupBox(tr("Clients"));
    QGridLayout *layout = new QGridLayout;
    clientListBox->setLayout(layout);
}

void MainWindow::createRuntimeList(){
    runtimeListBox = new QGroupBox(tr("Runtimes"));
    QGridLayout *layout = new QGridLayout;
    runtimeListBox->setLayout(layout);
}


void MainWindow::createConsole(){

    consoleBox = new QGroupBox(tr("Console"));
    QGridLayout *layout = new QGridLayout;

    QTextEdit* consoleOutput = new QTextEdit();
    consoleOutput->setReadOnly(true);
    consoleOutput->setLineWrapMode(QTextEdit::NoWrap);

    QFont font = consoleOutput->font();
    font.setFamily("Courier");
    font.setPointSize(10);
    consoleOutput->setFont(font);

    layout->addWidget(consoleOutput);


    QLineEdit* consoleInput = new QLineEdit();

    std::function<void()> consoleInputListener = [consoleOutput,consoleInput,this] ()->void {

            std::cout << "command: "<<consoleInput->text().toStdString() <<std::endl;
            consoleOutput->append(consoleInput->text());
            consoleOutput->moveCursor(QTextCursor::End);
            //consoleOutput->setCurrentFont(font)
            //logOutput.setTextColor(color)

            //logOutput.insertPlainText(text)

            QScrollBar* sb = consoleOutput->verticalScrollBar();
            sb->setValue(sb->maximum());
    };
    connect(consoleInput,&QLineEdit::returnPressed,this,consoleInputListener);
    consoleInput->setText("your console");
    layout->addWidget(consoleInput);
    consoleBox->setLayout(layout);

}

void MainWindow::createProfilingOverview(){
    profilingBox = new QGroupBox(tr("Profiling"));
    QGridLayout *layout = new QGridLayout;
    profilingBox->setLayout(layout);
}

void MainWindow::createProfilingPage(){
    profilePage = new QGroupBox(tr("Profiling"));
    QGridLayout *layout = new QGridLayout;
    profilePage->setLayout(layout);
}
