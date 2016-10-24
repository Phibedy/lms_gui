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

    clientTable = new QTableWidget;
    clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    clientTable->setSelectionMode(QAbstractItemView::SingleSelection);
    clientTable->verticalHeader()->setVisible(false);
    clientTable->setShowGrid(false);
    clientTable->setRowCount(1);
    clientTable->setColumnCount(2);
    QStringList qlist;
    qlist<<"FD"<<"PEER";
    clientTable->setHorizontalHeaderLabels(qlist);

    clientTable->setItem(0, 0, new QTableWidgetItem("4"));
    clientTable->setItem(0, 1, new QTableWidgetItem("unix"));
    layout->addWidget(clientTable);
    clientListBox->setLayout(layout);
}

void Overview::createRuntimeList(){
    runtimeListBox = new QGroupBox(tr("Runtimes"));
    QGridLayout *layout = new QGridLayout;

    runtimeTable = new QTableWidget;
    runtimeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    runtimeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    runtimeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    runtimeTable->verticalHeader()->setVisible(false);
    runtimeTable->setShowGrid(false);
    runtimeTable->setRowCount(1);
    runtimeTable->setColumnCount(2);
    QStringList qlist;
    qlist<<"ID"<<"CONFIG";
    runtimeTable->setHorizontalHeaderLabels(qlist);

    runtimeTable->setItem(0, 0, new QTableWidgetItem("1"));
    runtimeTable->setItem(0, 1, new QTableWidgetItem("/dev/null - sorry"));
    layout->addWidget(runtimeTable);
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
