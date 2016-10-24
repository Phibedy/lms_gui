#include "graph.h"
#include <iostream>
#include <QImageReader>

Graph::Graph(){
    QVBoxLayout *layout = new QVBoxLayout;
    graphLabel = new QLabel();
    graphLabel->setText("Loading");
    layout->addWidget(graphLabel);
    setLayout(layout);
}

bool Graph::createGraph(){
    bool success = false;
    QString filename = "";
    //TODO create dot graph
    //TODO create png
    //TODO save png
    if(success){
        if(loadGraph(filename))
            return true;
    }
    return false;
}


bool Graph::loadGraph(const QString &fileName){
    QImageReader reader(fileName);
    //reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull())
        return false;
    setGraph(newImage);
    return true;
}


void Graph::setGraph(const QImage &newImage){
    graph = newImage;
    graphLabel->setPixmap(QPixmap::fromImage(graph));
    graphLabel->setText("");
}
