#ifndef QDROPBOX_H
#define QDROPBOX_H
#include <abstractsave.h>

class QDropbox  : public AbstractSave
{

public:

    virtual bool copyDirectoryTree(QStringList dirs);
    virtual bool copyFilesToDir(QStringList files);
    virtual bool copyStructure(QStringList dirs, QStringList files);

};

#endif // QDROPBOX_H
