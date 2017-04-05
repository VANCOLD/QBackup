#ifndef QXMLPARSER_H
#define QXMLPARSER_H
#include <QString>
#include <QStringList>
#include <QXmlStreamReader>
#include <QFileInfo>

class QXmlParser
{


public:

    //*** Konstruktoren ***//

        // Hauptkonstruktor. Liest die Daten eines <dir> Tags aus und speichert sie in den Objekt-Instanzvariablen
        QXmlParser(QXmlStreamReader *reader);

        // Default-Kontruktor
        QXmlParser();

    //*** ENDE Konstruktoren ***//



    //*** GETTER-FUNKTIONEN ***//

        // Gibt den Ordner-Pfad zurück, des eingelesenen <dPath> tags
        QString getDirPath();

        // Gibt die gültigen Filter zurück, des eingelesenen <filter> tags
        QStringList getFilters();

        // Gibt die exkludierten Ordner zurück, des eingelesenen <excluded> tags
        QStringList getExcludedDirs();

        // Gibt an ob die eingelesen Ordner-Daten gültig sind (true: gültig; false: ungültig)
        bool isValid();

    //*** ENDE GETTER-FUNKTIONEN ***//

private:


    // Pfad eines Ordners, der für die Backup-Routine bestimmt ist
    QString path;

    // QStringList, welche die Dateiendungen speichert. Nach diesen Endungen werden im Ordner mit dem Pfad von path gesucht.
    QStringList filters;

    // QStringList, welche die Ordner beinhaltet, welche beim Backup vorgang übersprungen werden sollen.
    QStringList excluded;

    // Gibt an ob dieses QXmlParser Objekt gültig / nutzbare oder ungültige / nicht nutzbare Daten enthält.
    bool valid;

};

#endif // QXMLPARSER_H
