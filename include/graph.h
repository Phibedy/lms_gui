#ifndef LMS_GUI_GRAPH
#define LMS_GUI_GRAPH

#include <QtWidgets>

class Graph:public QWidget{
    Q_OBJECT
public:
    Graph();
private:
    QImage graph;
    QLabel *graphLabel;
    bool graphAvailable(){
        return graph.width() > 0;
    }
    bool createGraph();
    bool loadGraph(const QString &fileName);
    void setGraph(const QImage &newImage);
};
#endif //LMS_GUI_GRAPH
