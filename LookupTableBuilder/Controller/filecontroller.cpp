#include "filecontroller.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>

FileController::FileController(QObject *parent) :
        QObject(parent)
{
    myFile.setFileName("");
}

void FileController::setFile(QString file_name)
{
    myFile.setFileName(file_name);
}

QString FileController::getFileName()
{
    return myFile.fileName();
}

bool FileController::readFile(QList<QVector2D> &data)
{
    if(myFile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&myFile);
        QTextStream in(&myFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList line_parts = line.split(",", QString::SkipEmptyParts);
            if(line_parts.size() != 2)
                continue;
            QVector2D vec(line_parts.at(0).toDouble(), line_parts.at(1).toDouble());
            data.push_back(vec);
        }
        return true;
        myFile.close();
    }
    return false;
}

void FileController::appendPair(qreal x, qreal y)
{
    myFile.close();
    if(myFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&myFile);
        stream << x << ", " << y << endl;
        myFile.flush();
        myFile.close();
    }
}

void FileController::clearFile()
{
    myFile.close();
    if(myFile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        myFile.close();
    }
}

