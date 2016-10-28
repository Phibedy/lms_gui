#include "logging.h"
#include <iostream>

Logging::Logging(){
    QVBoxLayout *layout = new QVBoxLayout;


    filterBox = new QGroupBox(tr("Filter"));
    QGridLayout *filterLayout = new QGridLayout;
    //filterLayout->addWidget(clientTable);

    QComboBox *moduleSelector = new QComboBox;
    moduleSelector->addItem("All");
    moduleSelector->addItem("Module 1");
    moduleSelector->addItem("Module 2");
    moduleSelector->addItem("Module 3");
    QComboBox *typeSelector = new QComboBox;
    typeSelector->addItem("Debug");
    typeSelector->addItem("Info");
    typeSelector->addItem("Warn");
    typeSelector->addItem("Error");
    filterLayout->addWidget(moduleSelector,0,0);
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
    messageTable->setColumnCount(4);
    messageTable->horizontalHeader()->setStretchLastSection(true);
    QStringList qlist;
    qlist<<"Module"<<"Suffix"<<"Type"<<"Message";
    messageTable->setHorizontalHeaderLabels(qlist);
    layout->addWidget(messageTable);
    setLayout(layout);
}
