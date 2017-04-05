#ifndef ABSTRACTSAVE_H
#define ABSTRACTSAVE_H

#include <QStringList>


class AbstractSave
{


public:
    AbstractSave();

    bool copyDirectoryTree(QStringList dirs);
    bool copyFilesToDir(QStringList files);
    bool copyStructure(QStringList dirs, QStringList files);


};

#endif // ABSTRACTSAVE_H
