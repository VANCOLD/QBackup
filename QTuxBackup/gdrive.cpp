#include "gdrive.h"

bool QGoogleDrive::copyDirectoryTree(QStringList dirs)
{
    return true;
}


bool QGoogleDrive::copyFilesToDir(QStringList files)
{
    return true;
}


bool QGoogleDrive::copyStructure(QStringList dirs, QStringList files)
{


    if(this->copyDirectoryTree(dirs) && this->copyFilesToDir(files) )
        return true;



    return false;
}
