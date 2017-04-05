#include "qxmlparser.h"


/*
 * Hauptkonstruktor
 *
 * Dieser Konstruktor übernimmt ein QXmlStreamReader pointer, welcher zum Auslesen
 * der Tags im File genutzt wird.
 * Es gibt hier 3 Tags die wichtig sind, filter,excluded und dPath
 *
 * Diese werden gespeichert, falls das Objekt aber keine gültigen
 * Daten enthält wird es als invalid makiert. In diesem Fall würde
 * das Programm dieses Objekt verwerfen
 *
 */
QXmlParser::QXmlParser(QXmlStreamReader *reader)
{

    // Deklarieren und initialisieren der Instanzvariablen (mit default-werten)
    path     = "";
    excluded = QStringList();
    filters  = QStringList();


    // Solange der Endtag dir nicht kommt und kein Fehler auftritt soll die Schleife ausgeführt werden
    while((reader->name() != "dir") && !reader->hasError())
    {
        // Nächstes Element des XML-Files auslesen
        QXmlStreamReader::TokenType token = reader->readNext();


        // Wenn es ein "start" tag ist dann soll der Name überprüft werden
        if(token == QXmlStreamReader::StartElement)
        {

            // Ist der Name des Tags filter?
            if(reader->name() == "filter")
                // Wenn er filter ist, dann liest man aus reader den Text und teilt bei dem Steuerzeichen ; den String auf
                this->filters << reader->readElementText().split(';');


            // Ist der Name des Tags dPath?
            if(reader->name() == "dPath")
                // Wenn er dPath ist, liest man aus reader den Wert aus (String) und speichert Ihn in path
                this->path = reader->readElementText();

            // Ist der Name des Tags excluded?
            if(reader->name() == "excluded")
                // Wenn er filter ist, dann liest man aus reader den Text und teilt bei dem Steuerzeichen ; den String auf
                this->excluded = reader->readElementText().split(";");

        }

    }

    // Hier wird überprüft ob path nicht leer ist UND ob der angegebene Pfad existiert
    if(path.count() && QFileInfo(path).exists())
        // Falls er das tut, ist dieser Pfad gültig
        valid = true;
}


/*
 * Default Konstruktor
 *
 * Setzt die Werte für die Instanzvariablen auf ihre Default-Werte
 */
QXmlParser::QXmlParser()
{

    this->valid     = false;
    this->path      = "";
    this->excluded  = QStringList();
    this->filters   = QStringList();

}


// Gibt den Pfad des QXmlParser zurück. (Dieser würde von einem <dir> </dir> Element entnommen)
QString QXmlParser::getDirPath() {
    return this->path;
}

// Gibt die excludierten Ordners des QXmlParser zurück. (Dieser würde von einem <dir> </dir> Element entnommen)
QStringList QXmlParser::getExcludedDirs() {
    return this->excluded;
}


// Gibt die filter des QXmlParser zurück. (Dieser würde von einem <dir> </dir> Element entnommen)
QStringList QXmlParser::getFilters() {
    return this->filters;
}


// isValid gibt an, ob der eingelesene <dir> </dir> Tag Inhalt ein gültiges Verzeichnis ist (d.h nutzbar)
bool QXmlParser::isValid() {
    return this->valid;
}

