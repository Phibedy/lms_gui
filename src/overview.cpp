#include "overview.h"
#include <iostream>

Overview::Overview(){
    QVBoxLayout *overviewLayout = new QVBoxLayout;

    createClientList();
    createConsole();
    createProfilingOverview();
    createRuntimeList();
    overviewLayout->addWidget(clientListBox);
    overviewLayout->addWidget(runtimeListBox);
    overviewLayout->addWidget(consoleBox);
    setLayout(overviewLayout);
}


void Overview::createClientList(){
    clientListBox = new QGroupBox(tr("Clients"));
    QGridLayout *layout = new QGridLayout;
    clientListBox->setLayout(layout);
}

void Overview::createRuntimeList(){
    runtimeListBox = new QGroupBox(tr("Runtimes"));
    QGridLayout *layout = new QGridLayout;
    runtimeListBox->setLayout(layout);
}


void Overview::createConsole(){

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

void Overview::createProfilingOverview(){
    profilingBox = new QGroupBox(tr("Profiling"));
    QGridLayout *layout = new QGridLayout;
    profilingBox->setLayout(layout);
}
