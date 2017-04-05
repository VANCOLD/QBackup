#include "qbackupmanager.h"



QBackupManager::QBackupManager(QObject *parent) : QObject(parent)
{
    this->finished = false;
}




void QBackupManager::init()
{
    QList<QXmlParser> dirs;


    if(this->readXML(dirs)) {

        foreach(QXmlParser element,dirs)
        {

            // Input-Feld
            QString path = element.getDirPath();

            // QFileInfo Objekt, es dient zur Überprüfung welche Art von Datei der angegebene Pfad ist (File oder Ordner) und ob der Pfad existiert.
            QFileInfo check = QFileInfo(path);


            // QFileInfo kann überprüfen ob ein/e  Datei/Ordner existiert.
            // Also wenn der Pfad existiert und ein Ordner ist dann führt sich der Hauptblock aus
            if(check.exists() && check.isDir())
            {

                qDebug() << "";
                qDebug() << "[DEBUG] Pfad: " + element.getDirPath() + " existiert!";
                /*
                 * Hier gibt es 2 Fälle: Wenn der Pfad ein root ist (D.h C:\, D:\ ect) dann soll überprüft werden ob der Pfad ein \ hat
                 * Wenn nein soll es hinzugefügt werden, bei ja passiert nichts.
                 * Falls es kein Root-Ordner ist dann wird überprüft OB der Pfad mit einem \ endet.
                 * Wenn ja soll es entfernt werden, ansonsten nicht
                 */
                path = !path.endsWith(QDir::separator()) ? path + QDir::separator() : path;

                /* Das Such Objekt. Hier werden für ein QDirNode Objekt such-queries eingegeben. Pro QDirNode Root ein search.
                *  Gleichzeitig setze ich den Filter für das QDir-Object. Dieses ist eine QStringList und die QStringList Werte (Datei-Endungen) die drinnen stehen werden dann
                *  In der Daten-struktur gesucht (wird vom QDirNode gemacht;)
                */
                QDir search = QDir();
                search.setNameFilters(element.getFilters());

                // Hier erstelle ich mein QDirNode Objekt. Dazu benötige ich einen QString (Pfad) und ein QDir (ein Objekt zum Suchen)
                QDirNode ordner = QDirNode(&path,QString(),search,element.getExcludedDirs());

                qDebug() << "";
                qDebug() << "[DEBUG] Struktur wurde angelegt!";


                this->directories << ordner;

                int dir = 0, file = 0;
                ordner.getStructureDataCount(dir,file);
                qDebug() << "Ordner Anzahl: " << dir << "; Fileanzahl:" << file;
            }

        }


    } else
    {
        qDebug() << "Struktur konnte nicht erstellt werden!";
        return;
    }
    qDebug() << "Struktur ist fertig";

}




bool QBackupManager::readXML(QList<QXmlParser> &dirs) {


    // File welches ausgelesen werden soll
    QFile xmlFile(QDir::currentPath() + "/backup-data.xml");
    // Öffnen des Files mit Lese-Rechten
    xmlFile.open(QFile::ReadOnly | QFile::Text);


    // Lese-Objekt; liest aus dem iniFile aus
    QXmlStreamReader reader(&xmlFile);


    while(!reader.atEnd() && !reader.hasError())
    {

        // Read next element
        QXmlStreamReader::TokenType token = reader.readNext();


        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument)
            continue;



        //If token is StartElement - read it
       if(token == QXmlStreamReader::StartElement)
       {


           if(reader.name() == "dir")
           {

                reader.readNext();

                QXmlParser buff = QXmlParser(&reader);

                if(buff.isValid())
                {
                    qDebug() << "";
                    qDebug() << "[DEBUG] Pfad gefunden! " + buff.getDirPath();
                    dirs << buff;
                }
           }
       }

    }

    return dirs.length() ? true : false;

}




void QBackupManager::executeCycle()
{
    QDateTime timestamp = QDateTime::currentDateTime();

}




void QBackupManager::save() {

}





void QBackupManager::update() {

}





bool QBackupManager::isFinished() {
    return true;
}
