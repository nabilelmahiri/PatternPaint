#include "projectfile.h"

#include <QDebug>
#include <QSettings>

ProjectFile::ProjectFile()
{

}


bool ProjectFile::save(QString filename, Scene *scene, PatternCollection *patternCollection)
{

    qDebug() << "Save project:" << filename;

    // Create a new file
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "Project save failed!";
        return false;
    }

    QDataStream out(&file);

    // write header
    writeHeader(out, PROJECT_FORMAT_VERSION);

    out << scene;
    out << patternCollection;

    file.close();

    qDebug() << "Project successful saved";

    return true;
}


bool ProjectFile::open(QString filename, Scene *scene, PatternCollection *patternCollection)
{
    qDebug()<<"Open Project:" << filename;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<< "Error: Cannot read project file ";
        return false;
    }

    // read project file
    QDataStream in(&file);

    // read header
    if(readHeader(in) != PROJECT_FORMAT_VERSION){
        qDebug()<< "Error: Project version mismatch";
        return false;
    }

    in >> *(scene);
    in >> *(patternCollection);

    if(in.status() == QDataStream::Ok) {
        qDebug() << "Project successful read";
    }
    else {
        qDebug() << "Project read failed!";
        return false;
    }

    return true;
}

void ProjectFile::writeHeader(QDataStream &stream, float version)
{
    stream.setVersion(QDataStream::Qt_5_8);

    stream << (QString)PROJECT_HEADER;
    stream << version;
//    stream << (QString)GIT_VERSION;
}

float ProjectFile::readHeader(QDataStream &stream)
{
    QString header;
    float formatVersion;
//    QString patternPaintVersion;

    stream.setVersion(QDataStream::Qt_5_8);

    stream >> header;
    if(header != PROJECT_HEADER){
        qDebug()<< "Error: Header incorrectly";
        return 0;
    }

    stream >> formatVersion;

//    stream >> patternPaintVersion;
//    qDebug() << "Project created with Pattern Paint version:" << patternPaintVersion;

    return formatVersion;
}

