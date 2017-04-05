#ifndef QDIRNODE_H
#define QDIRNODE_H
#include <QString>
#include <QDir>
#include <QStringList>
#include <QMap>
#include <QDebug>
#include <QDateTime>

class QDirNode
{

public:


    // ** Konstruktoren ** //
        QDirNode(QString* path, QString dirPath ,QDir search,QStringList excluded);
        QDirNode();

        ~QDirNode();

     // ** Setter & Getter Funktionen ** //

        // Pfad Funktionen
        void getStructureDataCount(int &dirCount,int &fileCount);


    // ** QDirNode Abfrage & Bearbeitungs-Funktionen ** //

        // Die Funktion getDataPaths iteriert rekursiv durch alle QDirNodes und speichert die Inhalte und gibt diese zurück.
        void getDataPaths(QStringList &pathList);

        // Siehe Beschreibung getDataPaths; INFO: Unterschied ist das NUR File-Paths zurückgegeben werden
        void getFileNames(QStringList &nameList);

        // Siehe Beschreibung getDataPaths; INFO: Unterschied ist das NUR Directory-Paths zurückgegeben werden
        void getDirPaths(QStringList &pathList);

        // Siehe Beschreibung getDataPaths; INFO: Unterschied ist das NUR Directory-Paths zurückgegeben werden
        void getFilePaths(QStringList &pathList);

        // Speichert alle Files und Ordner in referenzierte QStringList Objekte (Werden intern genutzt und dann in data gespeichert).
        void fetchData(QDir search, QStringList &dirs);

        void createSubnodes(QStringList dirs, QDir search, QStringList excluded);

        void updateStructure(QDateTime timestamp);


// Diese Werte soll weitervererbt werden
private:

    // Unterverzeichnisse eines QDirNode Objekts (welches selbst ein Verzeichnis ist)
    QMap<QString,QDirNode> nodes;

    // In diese QStringList werden alle Daten (d.h Ordner und Files) gespeichert.
    QStringList data;

    // Unterordneranzahl im QDirNode-Objekt (Ordner)
    int dCount;

    // Pfad-Teil welches jeder Ordner im QDirNode-Konstrukt besitzt.
    QString *path;

    // Spezifische Verzweigung (Ordner Pfad) INNERHALB des QDirNode Konstrukts (wird benötigt zum Speichern)
    QString dirPath;

    // Fileanzahl dieses QDirNode-Objekts (Ordner)
    int fCount;

    QStringList searchFilter;

    QStringList excluded;

};





#endif // QDIRNODE_H
