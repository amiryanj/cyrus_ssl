#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QObject>
#include <QList>
#include "Logic/graph.h"
#include <QFile>

class FileController : public QObject
{
    Q_OBJECT
public:
    explicit FileController(QObject *parent = 0);

    void setFile(QString file_name);
    QString getFileName();
    bool readFile(QList<QVector2D> &data);

    void appenPair(qreal x, qreal y);
    void clearFile();
//    void saveRawData(QString fileName, QList<Graph*>& list, int w, int h);
//    void saveSteppedData(QString fileName, QList<Graph>& list, int stepMilli, int w, int h);

private:
    QFile myFile;

};

#endif // FILECONTROLLER_H
