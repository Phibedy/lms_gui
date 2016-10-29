#include "logging.h"
#include <iostream>

Logging::Logging(){
    QVBoxLayout *layout = new QVBoxLayout;


    filterBox = new QGroupBox(tr("Filter"));
    QGridLayout *filterLayout = new QGridLayout;
    QLineEdit *filterEdit = new QLineEdit;
    filterLayout->addWidget(filterEdit,0,0);

    std::function<void()> filterEditListener = [filterEdit,this] ()->void {
        filter(filterEdit->text());
    };
    connect(filterEdit,&QLineEdit::textChanged,this,filterEditListener);

    QComboBox *typeSelector = new QComboBox;
    typeSelector->addItem("Debug");
    typeSelector->addItem("Info");
    typeSelector->addItem("Warn");
    typeSelector->addItem("Error");
    filterLayout->addWidget(typeSelector,0,1);
    filterBox->setLayout(filterLayout);

    layout->addWidget(filterBox);

    messageTable = new QTableWidget;
    messageTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    messageTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    messageTable->setSelectionMode(QAbstractItemView::SingleSelection);
    messageTable->verticalHeader()->setVisible(false);
    messageTable->setShowGrid(false);
    messageTable->setRowCount(1);
    messageTable->setColumnCount(3);
    messageTable->horizontalHeader()->setStretchLastSection(true);
    QStringList qlist;
    qlist<<"Tag"<<"Type"<<"Message";
    messageTable->setHorizontalHeaderLabels(qlist);
    layout->addWidget(messageTable);
    setLayout(layout);
}


void Logging::filter(const QString &s){
    //TODO
    std::cout << "filterEdit: "<<s.toStdString() <<std::endl;
}
