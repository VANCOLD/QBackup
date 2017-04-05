#ifndef QGOOGLEDRIVE_H
#define QGOOGLEDRIVE_H
#include <abstractsave.h>



class QGoogleDrive : public AbstractSave
{

public:

    virtual bool copyDirectoryTree(QStringList dirs);
    virtual bool copyFilesToDir(QStringList files);
    virtual bool copyStructure(QStringList dirs, QStringList files);

};

#endif // QGOOGLEDRIVE_H
