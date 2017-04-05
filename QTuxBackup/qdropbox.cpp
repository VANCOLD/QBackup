#include "qdropbox.h"

bool QDropbox::copyDirectoryTree(QStringList dirs)
{
    return true;
}


bool QDropbox::copyFilesToDir(QStringList files)
{
    return true;
}


bool QDropbox::copyStructure(QStringList dirs, QStringList files)
{


    if(this->copyDirectoryTree(dirs) && this->copyFilesToDir(files) )
        return true;



    return false;
}
