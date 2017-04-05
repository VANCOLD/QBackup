#include "qdirnode.h"
#include <QStringBuilder>

// Default Konstruktor
QDirNode::QDirNode(){}

/*
 * Hauptkonstruktor
 *
 * Erstellt das derzeitige QDirNode, die Unter-Nodes und übergibt und filtert die Files
 * welche später zur Bearbeitung und Abfrage benötigt wird.
 * Excluded sind die Ordner, welche nicht zum QDirNode-Tree hinzugefügt werden sollen.
 *
 * Der Konstruktor setzt zuerst die Grundwerte, und springt dann in 2 Unterfunktionen,
 * nämlich:
 * fetchData(QStringList dirs,QStringList files)
 *
 * Diese Funktion holt sich alle zulässigen Informationen zum derzeitigen Verzeichnis das erstellt wird und speichert diese
 * in die dirs und files Referenz
 *
 *
 * UND
 *
 *
 * createSubnodes(dirs,search,excluded)
 *
 * Diese Funktion erstellt mit den Werten in Dirs Unterverzeichnisse (diese müssen relevante Daten enthalten; d.h Files)
 * excluded wird übergeben damit die Verzeichnisse die übersprungen werden sollen auch an die Unterverzeichnisse weitergegeben werden (falls sich dort ein exclude befindet)
 */
QDirNode::QDirNode(QString* path, QString dirPath,QDir search, QStringList excluded)
{

    QStringList buff    = search.nameFilters();
    this->searchFilter  = buff;
	/* 
	 * Update excluded; excluded should be a pointer variable; Additionally excluded should only contain a value if a sub-directory is inside the exclude
	 * list; The subfolders should be stored in the corresponding directory.
	*/
    this->excluded      = excluded;
    this->path          = path;
    this->dirPath       = dirPath;

    // QMap welche Pfad-Zweig-Namen und zugehöriges QDirNode speichert.
    this->nodes         = QMap<QString,QDirNode>();

    // Initialisierung der File & Ordner Counter
    this->dCount        = 0;
    this->fCount        = 0;


    QStringList dirs;
    // Hier werden die Unterordner erstellt und Ordner-Anzahl, File-Anzahl und das Daten-Objekt (data) erstellt und mit Werten befüllt

    this->fetchData(search,dirs);
    this->createSubnodes(dirs,search,this->excluded);


}


QDirNode::~QDirNode()
{
    delete this->path;
}


/*
 * Fragt Daten im derzeitigen Ordner-Punkt ab (Node)
 * Gespeichert werden Unterordner-Namen & File-Namen, weiters werden Anzahl gespeichert
 * und die Files dem Daten QStringList übergeben
 */
void QDirNode::fetchData(QDir search,QStringList &dirs)
{

    // Hier wird der Pfad des Such-Objekts auf den derzeitgen Ordner gesetzt
    search.setPath(*path + this->dirPath);

    /*
    * In dirs werden alle Daten die von search.entryList gefunden worden sind gespeichert
    * Diese sind Daten über die Ordner, nämlich die Namen der vorhanden Ordner
    */
    dirs   = search.entryList(QStringList(),QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::NoSymLinks);

    // Hier wird das gleiche gemacht wie bei dirs, bloss das man nach Files suicht (mit einem File-Filter)
    QStringList files  = search.entryList(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    // Anzahl der Files im ordner die in das Suchmuster passen; Wird einem internen Speicher übergeben
    this->fCount 	   =  files.size();

    // Hier werden alle im Ordner vorhanden Files in Daten geschrieben
    this->data << files;
}


/*
 * Erstellt die Unterverzeichnisse (der Baumstruktur; Sind QDirNodes)
 * Das wird ermöglicht durch die Übergabe eines QStringList (enthält Unterverzeichnis-Namen)
 *
 * Zusätzlich wird das Such Object jedem Unterverzeichnis per Referenz übergeben und
 * die Ordner welche nicht in den QDirNode-Baum aufgenommen werden sollen.
 * Ausgeschlossen sind excludierte Ordner ODER leere Ordner (Wenn ein Ordner Unterordner beinhaltet, aber dieser keine
 * relevanten Unterordner die Files enthalten)
 */
void QDirNode::createSubnodes(QStringList dirs, QDir search, QStringList excluded)
{


    // Hier werden die QDirNodes instanziert. Die neuen Pfade haben immer ein \ und den Namen
    // Diese zusammengesetzten Pfad werden mit dem + Operator kombiniert und dem QDirNode-Konstruktur übergeben
    foreach(QString dir, dirs)
    {

        // Buffer-Objekt zur Überprüfung von Ordner-Anzahl / File-Anzahl
        QDirNode buff = QDirNode(path, !this->dirPath.isEmpty() ? this->dirPath + QDir::separator() + dir : dir,search,this->excluded);

        if(!excluded.contains(*buff.path + buff.dirPath))
        {

        // Falls das dieser Ordner Files oder einen unterordner enthält soll er hinzugefügt werden;
        // Dadurch das buff vorher erstellt wird, passiert bei der Abfrage folgendes: Alle Unterordner wurden vorher instanziert, wenn Sie leer sind existieren sie nicht im
        // jetztigen buff Objekt. Daher wird es nur gespeichert wenn es entsprechende Files hat (welche vom Such-Objekt bestimmt werden)
            if(buff.dCount | buff.fCount)
            {

                // Das QDirNode zur nodes QList hinzufügen
                this->nodes.insert(dir,buff);
                // Hier wird der Ordnername zu einer Map hinzgefügt (der Index ist für die Nodes; Es vereinfacht das suchen)
                // Ordner-Anzahl erhöhen (int)
                this->dCount += 1;

            } // END IF buff.dCount | buff.fCount


        } else {
            excluded.removeOne(*buff.path + this->dirPath);
        } // END IF !excluded.contains(buff.path)


    } // END FOREACH
}


/*
 * Die Zähl-Funktion.
 * Speichert die Anzahl von Ordner und Files auf zwei seperate int pointer (dirCount & fileCount)
 * Dannach wird mit einer Foreach-Schleife jeder Unterordner rekursiv aufgerufen (Falls welche vorhanden sind)
 */
void QDirNode::getStructureDataCount(int &dirCount, int &fileCount)
{


    // Ordner-Anzahl & File-Anzahl des derzeitigen ordners zum Referenz-Int-Speicher hinzufügen
    dirCount  += this->dCount;
    fileCount += this->fCount;


    // Hier iteriere ich durch die Sub-Nodes mit einer Foreach schleife.
    // node ist ein Zwischenspeicher Objekt um einfachen Zugriff auf die QDirNodes zu bekommen
    foreach(QDirNode node,this->nodes.values())

        // Hier ruft das Programm die Funktion getStructureDataCount auf um die Unterordner zu durchsuchen
        node.getStructureDataCount(dirCount,fileCount);
}


/*
 * Diese Funktion speichert alle Pfad in dem QDirNode-Baum und gibt Sie mithilfe eines referenzierten QStringList Speichers zurück (kein Rückgabe Typ!)
 * Die Funktion erstellt einen Buffer und speichert die Daten des derzeitigen Nodes darin.
 * Dannach wird mit einer foreach Schleife jeder Unterordner rekursiv aufgerufen
 *
 * Wenn dieser Vorgang fertig ist werden die Pfade, welche noch in add gespeichert wurden hinzugefügt (daher ein Bottom-Up Pfade Ergebniss; D.h die untersten
 * Elemente zuerst, dann die obersten [bei der Ausgabe] )
 */
void QDirNode::getDataPaths(QStringList &pathList)
{
    if(this->fCount)
    {
        // Hier werden alle Inhalte aus dem jetztigen QDirNode in eine QStringList gespeichert.
        foreach(QString save, this->data)
            pathList << *path + this->dirPath + QDir::separator() + save;

    }


    if(!this->dCount)
    {
        pathList <<  *path;


    } else {

        foreach(QDirNode node,this->nodes.values())
            // Wenn ja dann durchsuche diesen Unterordner
            node.getDataPaths(pathList);
    }

}


void QDirNode::getFilePaths(QStringList &pathList)
{

    if(this->fCount)
    {
        // Hier werden alle Inhalte aus dem jetztigen QDirNode in eine QStringList gespeichert.
        foreach(QString save, this->data)
            pathList << *path + this->dirPath + QDir::separator() + save;


    }


    if(this->dCount)
    {
        foreach(QDirNode node,this->nodes.values())
            // Wenn ja dann durchsuche diesen Unterordner
            node.getFilePaths(pathList);
    }

}


void QDirNode::getDirPaths(QStringList &pathList)
{

    if(!this->dCount)
    {
        pathList << this->dirPath;


    } else {

        foreach(QDirNode node,this->nodes.values())
            // Wenn ja dann durchsuche diesen Unterordner
            node.getDirPaths(pathList);
    }

}

void QDirNode::updateStructure(QDateTime timestamp)
{

}
