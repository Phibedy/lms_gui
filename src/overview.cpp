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
    clientTable->setRowCount(0);
    clientTable->setColumnCount(2);
    QStringList qlist;
    qlist<<"FD"<<"PEER";
    clientTable->setHorizontalHeaderLabels(qlist);
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
    runtimeTable->setRowCount(0);
    runtimeTable->setColumnCount(2);
    runtimeTable->horizontalHeader()->setStretchLastSection(true);
    QStringList qlist;
    qlist<<"ID"<<"CONFIG";
    runtimeTable->setHorizontalHeaderLabels(qlist);
    layout->addWidget(runtimeTable);
    runtimeListBox->setLayout(layout);
    this->connect(runtimeTable, SIGNAL(itemSelectionChanged()), this, SLOT(test()));

}

void Overview::test(){
    std::cout<<"HALLo"<<std::endl;
}

void Overview::runtimeSelected(int row, int col){
    std::cout<<"SELECTED"<<row<<" "<<col<<std::endl;
}


void Overview::createConsole(){

    consoleBox = new QGroupBox(tr("Console"));
    QGridLayout *layout = new QGridLayout;

    consoleOutput = new QTextEdit();
    consoleOutput->setReadOnly(true);
    consoleOutput->setLineWrapMode(QTextEdit::NoWrap);

    QFont font = consoleOutput->font();
    font.setFamily("Courier");
    font.setPointSize(10);
    consoleOutput->setFont(font);

    layout->addWidget(consoleOutput);


    QLineEdit* consoleInput = new QLineEdit();

    std::function<void()> consoleInputListener = [consoleInput,this] ()->void {

            std::cout << "command: "<<consoleInput->text().toStdString() <<std::endl;
            consoleOutput->append(consoleInput->text());
            consoleOutput->moveCursor(QTextCursor::End);
            QScrollBar* sb = consoleOutput->verticalScrollBar();
            sb->setValue(sb->maximum());
    };
    //TODO does not workconnect(consoleInput,&QLineEdit::returnPressed,this,consoleInputListener);
    consoleInput->setText("your console");
    layout->addWidget(consoleInput);
    consoleBox->setLayout(layout);

}

void Overview::createProfilingOverview(){
    profilingBox = new QGroupBox(tr("Profiling"));
    QGridLayout *layout = new QGridLayout;
    profilingBox->setLayout(layout);
}

void Overview::removeClients(){
    clientTable->setRowCount(clientTable->rowCount()+1);
    QStringList qlist;
    qlist<<"FD"<<"PEER";
    clientTable->clear();
    clientTable->setRowCount(0);
}

void Overview::addClient(std::string peer, std::int32_t fd){
    clientTable->setRowCount(clientTable->rowCount()+1);
    QStringList qlist;
    qlist<<"FD"<<"PEER";
    clientTable->setHorizontalHeaderLabels(qlist);
    clientTable->setItem(clientTable->rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(fd))));
    clientTable->setItem(clientTable->rowCount()-1, 1, new QTableWidgetItem(QString::fromStdString(peer)));
}

void Overview::logMessage(lms::logging::Level lvl, std::string tag, std::string text,lms::Time stamp){
    //TODO http://stackoverflow.com/questions/2857864/qtextedit-with-different-text-colors-qt-c
    consoleOutput->append(QString::fromStdString(tag+": " + text));
    consoleOutput->moveCursor(QTextCursor::End);
    QScrollBar* sb = consoleOutput->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void Overview::removeProcesses(){
    runtimeTable->clear();
    runtimeTable->setRowCount(0);
    QStringList qlist;
    qlist<<"ID"<<"CONFIG";
    runtimeTable->setHorizontalHeaderLabels(qlist);
}

void Overview::addProcess(std::int32_t pid,std::string configfile){
    QStringList qlist;
    qlist<<"ID"<<"CONFIG";
    runtimeTable->setHorizontalHeaderLabels(qlist);
    runtimeTable->setRowCount(runtimeTable->rowCount()+1);
    runtimeTable->setItem(runtimeTable->rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(pid))));
    runtimeTable->setItem(runtimeTable->rowCount()-1, 1, new QTableWidgetItem(QString::fromStdString(configfile)));
    //TODO does not workconnect(runtimeTable, SIGNAL(itemSelectionChanged()), this, SLOT(test()));
}

