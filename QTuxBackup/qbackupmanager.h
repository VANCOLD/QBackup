#ifndef QBACKUPMANAGER_H
#define QBACKUPMANAGER_H

#include <QObject>
#include <QTime>
#include <QFile>
#include <qdirnode.h>
#include <qxmlparser.h>
#include <QList>
#include <QDir>
#include <QDebug>
#include <QDateTime>



class QBackupManager : public QObject
{

    Q_OBJECT


public:


    explicit QBackupManager(QObject *parent = 0);


    void init();
    bool readXML(QList<QXmlParser> &dirs);


    void update();
    void save();
    void executeCycle();


    bool isFinished();




private:

    bool finished;
    QList<QDirNode> directories;


};

#endif // QBACKUPMANAGER_H
